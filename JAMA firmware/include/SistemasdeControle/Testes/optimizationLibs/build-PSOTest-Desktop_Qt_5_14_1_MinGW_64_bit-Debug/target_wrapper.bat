@echo off
SetLocal EnableDelayedExpansion
(set PATH=D:\Qt\5.14.1\mingw73_64\bin;!PATH!)
if defined QT_PLUGIN_PATH (
    set QT_PLUGIN_PATH=D:\Qt\5.14.1\mingw73_64\plugins;!QT_PLUGIN_PATH!
) else (
    set QT_PLUGIN_PATH=D:\Qt\5.14.1\mingw73_64\plugins
)
%*
EndLocal
