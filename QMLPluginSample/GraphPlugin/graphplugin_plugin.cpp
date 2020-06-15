#include "graphplugin_plugin.h"
#include "graphchart.h"

#include <qqml.h>

void GraphPluginPlugin::registerTypes(const char *uri)
{
    // @uri Openthinks.Graph
    qmlRegisterType<GraphChart>(uri, 1, 0, "GraphChart");
}

