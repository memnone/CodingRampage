/** @file Application.cpp
 * 
 * @author	Claudio Zito
 *
 * @copyright  Copyright (C) 2018 Claudio Zito, University of Birmingham, UK
 *
 * @based on Golem framework developed by Marek Kopicki & Claudio Zito
 *
 * @license  This file copy is licensed to you under the terms described in
 *           the License.txt file included in this distribution.
 *
 */

#include <Rampage/App/Application.h>
#include <Rampage/Sys/Data.h>

//------------------------------------------------------------------------------

using namespace rampage;

//------------------------------------------------------------------------------

Application::Application() : pXMLContext(NULL) {
}

Application::~Application() {
	pContext.reset();
	pParser.reset();
}

int Application::main(int argc, char *argv[]) {
	try {
		// Determine configuration file name
		std::string cfg;
		if (argc == 1) {
			// default configuration file name
			cfg.assign(argv[0]);
#ifdef WIN32
			size_t pos = cfg.rfind(".exe"); // Windows only
			if (pos != std::string::npos) cfg.erase(pos);
#endif
			cfg.append(".xml");
		}
		else
			cfg.assign(argv[1]);

		try {
			// Create XML parser and load configuration file
			pParser = XMLParser::load(cfg);
		}
		catch (const Message& msg) {
			std::cerr << msg.what() << std::endl;
			std::cout << "Usage: " << argv[0] << " <configuration_file> [<log_file>] [stdout|stderr]" << std::endl;
			return 1;
		}

		// Find program XML root context
		pXMLContext = pParser->getContextRoot()->getContextFirst("rampage");
		if (pXMLContext == NULL)
			throw MsgApplication(Message::LEVEL_CRIT, "Unknown configuration file: %s", cfg.c_str());

		// Create program context
		rampage::Context::Desc contextDesc;
		XMLData(contextDesc, pXMLContext);
		// log file
		if (argc >= 3) {
			struct FileMessageCallback : public MessageCallback {
				StreamMessageCallback console;
				std::ofstream file;
				FileMessageCallback(const char* name, StreamMessageCallback::Desc& desc) : file(name, std::ios_base::out | std::ios_base::trunc), console(desc) {}
				void write(const Message& message) {
					console.write(message);
					// append to file
					file << message.what();
				}
			};
			StreamMessageCallback::Desc desc;
			desc.enableFormat = argc >= 4;
			if (desc.enableFormat)
				desc.file = !std::strcmp(argv[3], "stderr") ? stderr : stdout;
			contextDesc.messageStreamDesc->messageCallback.reset(new FileMessageCallback(argv[2], desc));
		}

		pContext = contextDesc.create(); // throws
		
		// run application
		run(argc, argv);

		return 0;
	}
	catch (const Message& msg) {
		if (pContext != NULL)
			pContext->write(msg);
		else
			std::cerr << msg.what() << std::endl;
	}
	catch (const std::exception &ex) {
		const Message msg(Message::LEVEL_CRIT, "%s\n", ex.what());
		if (pContext != NULL)
			pContext->write(msg);
		else
			std::cerr << msg.what() << std::endl;
	}

	return 1;
}

//------------------------------------------------------------------------------
