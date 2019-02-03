#include <cstdio>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

void checkVersion(){LIBXML_TEST_VERSION}

static void
print_element_names(xmlNode * a_node)
{
	xmlNode *cur_node = NULL;

	for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
		if (cur_node->type == XML_ELEMENT_NODE) {
			printf("Node: %s\n", cur_node->name);
		}
		else if (cur_node->content)
		{
			std::string s = (char*)xmlNodeGetContent(cur_node);
			s.erase(s.find_last_not_of(" \n\r\t") + 1);
			//s.erase(s.find_first_of(" \n\r\t") + 1);
			std::cout << "\tcontents:[" << s << "]" << std::endl;
			//printf("\tcontent: [%s]\n", s.c_str());
		}
		print_element_names(cur_node->children);
	}
}

int main(int argc, char* argv[])
{
	printf("hello from xmlparser!\n");
	checkVersion();
	xmlKeepBlanksDefault(0);
	if (argc < 2)
	{
		printf("usage: %s <file.xml>\n", argv[0]);
		return -1;
	}
	xmlDocPtr doc = xmlParseFile(argv[1]);
	xmlNodePtr cur = xmlDocGetRootElement(doc);
	print_element_names(cur);
	return 0;
}
