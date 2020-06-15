#ifndef GRAPHPLUGIN_PLUGIN_H
#define GRAPHPLUGIN_PLUGIN_H

#include <QQmlExtensionPlugin>

class GraphPluginPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};

#endif // GRAPHPLUGIN_PLUGIN_H
