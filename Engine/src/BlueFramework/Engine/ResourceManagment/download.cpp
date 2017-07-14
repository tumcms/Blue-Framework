/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2016-2017 Technical University of Munich
    Chair of Computational Modeling and Simulation.

    BlueFramework is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    BlueFramework is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

// do not reorder the following two header files - otherwise compiler errors will occur
#include <SDKDDKVer.h>
#include <boost/asio.hpp>

#include "BlueFramework/Core/Diagnostics/log.h"
#include "BlueFramework/Core/Uri.h"
#include "BlueFramework/Core/string.h"
#include "BlueFramework/Engine/ResourceManagment/FileNotFound404Exception.h"
#include "BlueFramework/Engine/namespace.h"

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/filesystem.hpp>
#include <fstream>
#include <memory>

#include <tinyxml2.h>

#include "download.h"

using boost::asio::ip::tcp;

BLUEFRAMEWORK_ENGINE_NAMESPACE_BEGIN

std::string getHttpData(const std::string& server, const std::string& file) {
	try {
		boost::asio::ip::tcp::iostream s(server, "http");

		s.expires_from_now(boost::posix_time::seconds(60));

		if (!s) {
			throw "Unable to connect: " + s.error().message();
		}

		// ask for the file
		s << "GET " << file << " HTTP/1.0\r\n";
		s << "Host: " << server << "\r\n";
		s << "User-Agent: Mozilla/4.0";
		s << "Accept: */*\r\n";
		s << "Connection: close\r\n\r\n";

		// Check that response is OK.
		std::string http_version;
		s >> http_version;
		unsigned int status_code;
		s >> status_code;
		std::string status_message;
		std::getline(s, status_message);
		if (!s && http_version.substr(0, 5) != "HTTP/") {
			throw "Invalid response\n";
		}

		if (status_code != 200u) {
			if (status_code == 404u) {
				throw buw::FileNotFound404Exception(file);
			}
			if (status_code == 301u) {
				std::string header;
				/*while(std::getline(s, header) && header != "\r") {
				    if(header.substr(0, 8) == "Location") {
				        buw::Uri url(header.substr(10, header.size()));
				        return get_http_data(url.getHost(), url.getPath());
				    }
				}*/
				throw buw::Exception("Response returned with status code %u", status_code);
			} else
				throw buw::Exception("Response returned with status code %u", status_code);
		}

		// Process the response headers, which are terminated by a blank line.
		std::string header;
		while (std::getline(s, header) && header != "\r") {
		}

		// Write the remaining data to output.
		std::stringstream ss;
		ss << s.rdbuf();
		return ss.str();
	} catch (std::exception& e) {
		return e.what();
	}
}

void downloadFile(const downloadDescription& dd) {
	buw::Uri url(dd.uri);

	BLUE_LOG(info) << "Try to download " << url.getPath().c_str();

	std::string path = url.getPath();
	path = buw::replace(path, " ", "%20");

	std::string result = getHttpData(url.getHost(), path);

	boost::filesystem::path p(dd.localPath.c_str());
	if (!boost::filesystem::exists(p.parent_path())) {
		boost::filesystem::create_directories(p.parent_path());
	}

	std::stringstream ss;
	ss << dd.localPath.c_str();

	std::ofstream of(ss.str().c_str(), std::ios::binary);
	of << result;
	of.close();
}

void downloadFile(const std::string& uri, const std::string& localPath) {
	downloadDescription dd;
	dd.uri = uri;
	dd.localPath = localPath;
	downloadFile(dd);
}

void loadWebResources(const char* filename) {
	if (!boost::filesystem::exists(filename)) {
		BLUE_LOG(error) << "Resource file \"" << filename << "\" does not exist!";
		throw buw::Exception("Could not open %s.", filename);
	}

	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename);

	auto xmlResources = doc.FirstChildElement("resources");

	typedef std::pair<std::string, std::string> stringPair;
	std::vector<stringPair> resourceList;

	auto xmlResource = xmlResources->FirstChildElement("resource");
	for (; xmlResource != nullptr; xmlResource = xmlResource->NextSiblingElement()) {
		const char* textUriText = xmlResource->FirstChildElement("uri")->GetText();
		const char* textLocalPathText = xmlResource->FirstChildElement("localPath")->GetText();

		resourceList.push_back(stringPair(textUriText, textLocalPathText));
	}

	for (int i = 0; i < resourceList.size(); i++) {
		if (!boost::filesystem::exists(resourceList[i].second)) {
			downloadFile(resourceList[i].first, resourceList[i].second);
		}
	}
}

BLUEFRAMEWORK_ENGINE_NAMESPACE_END