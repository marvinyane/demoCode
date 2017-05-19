#include <string>
#include <libxml/tree.h>
#include <libxml/parser.h>

xmlNodePtr findChildNodeByName(xmlNodePtr parent, const char * name)
{

    xmlNodePtr cur = xmlFirstElementChild(parent);
    for (; cur != NULL; cur = xmlNextElementSibling(cur))
    {

        if (!xmlStrcasecmp(cur->name, BAD_CAST(name)))
        {

            return cur;
        }
    }
    return NULL;
}

std::string createXml()
{
    std::string start = "";
    std::string appListEnd = "</app></appList>";
    std::string total = "";

    start.append("<appList><app>");
    start.append("<appID>0x00000001</appID>");
    start.append("<name>......</name>");
    start.append("<variant></variant>");
    start.append("<providerName></providerName>");
    total = start + appListEnd;

    return total;
}

int main() 
{
    xmlDocPtr document = xmlReadFile("./service.xml", "UTF-8", XML_PARSE_NOENT);
    
    xmlNodePtr rootElement = xmlDocGetRootElement(document);
    
    printf("root element is %p\n", rootElement);

    if (NULL != rootElement) {
        xmlNodePtr services = rootElement->children;
        for (; services != NULL; services = services->next) {

            if (xmlStrcmp(services->name, (const xmlChar*)"service")) {
                continue;
            }

            xmlNodePtr name = findChildNodeByName(services, "name");
            if (name) {
                xmlChar *str = xmlNodeGetContent(name);
                printf("xml node is %s \n", (char*)str);
                xmlFree(str);
            }
            else {
                // TODO:
                continue;
            }

            xmlNodePtr processName = findChildNodeByName(services, "processName");
            if (processName) {
                xmlChar *str = xmlNodeGetContent(processName);
                printf("xml node is %s \n", (char*)str);
                xmlFree(str);
            }
            else {
                // TODO:
                continue;
            }
        }
    }
    else {
        printf("path is open or parse failed.\n");
    }

    return 0;
}
