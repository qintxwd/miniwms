﻿#include "configure.h"
#include <QSettings>
#include <QDebug>
Configure::Configure(): config_file("./config.conf")
{

}

void Configure::setConfigFile(const QString &file)
{
    config_file = file;
}

void Configure::load()
{
    config_map.clear();
    QSettings settings(config_file, QSettings::IniFormat);
    QStringList keys = settings.allKeys();
    for(QString key : keys)
    {
        config_map.insert(key,settings.value(key));
    }

    //这里有两种方案。
    //方案1.这里判定有些设置是否存在，如果不存在，那么在添加默认值.
    //方案2.在getvalue调用后，判断isvalid。然后给默认值.

    //这里讲采用方案1，其他处的代码会规整很多
    if(!config_map.contains("solution/type")){
        //方案A[36个货物存放点]
        //方案B[48个货物存放点]
        //方案C[60个货物存放点]
        config_map.insert("solution/type","C");
    }

    if(!config_map.contains("solutionA/row")){
        //方案A的行数
        config_map.insert("solutionA/row",4);
    }
    if(!config_map.contains("solutionB/row")){
        //方案B的行数
        config_map.insert("solutionB/row",6);
    }
    if(!config_map.contains("solutionC/row")){
        //方案C的行数
        config_map.insert("solutionC/row",5);
    }

    if(!config_map.contains("solutionA/column")){
        //方案A的列数
        config_map.insert("solutionA/column",9);
    }
    if(!config_map.contains("solutionB/column")){
        //方案B的列数
        config_map.insert("solutionB/column",9);
    }
    if(!config_map.contains("solutionC/column")){
        //方案C的列数
        config_map.insert("solutionC/column",12);
    }

    if(!config_map.contains("solutionA/rowA")){
        //方案A的货物A的行数
        config_map.insert("solutionA/rowA",3);
    }
    if(!config_map.contains("solutionB/rowA")){
        //方案B的货物A的行数
        config_map.insert("solutionB/rowA",3);
    }
    if(!config_map.contains("solutionC/rowA")){
        //方案C的货物A的行数
        config_map.insert("solutionC/rowA",3);
    }


    if(!config_map.contains("ui/good_width")){
        config_map.insert("ui/good_width",90);
    }
    if(!config_map.contains("ui/good_height")){
        config_map.insert("ui/good_height",125);
    }

    if(!config_map.contains("ui/good_margin")){
        config_map.insert("ui/good_margin",10);
    }
    if(!config_map.contains("ui/good_spacing")){
        config_map.insert("ui/good_spacing",5);
    }
    if(config_map.contains("RadioFrequency/COM")){
        config_map.insert("RadioFrequency/COM","COM1");
    }
    if(config_map.contains("RadioFrequency/Parity")){
        config_map.insert("RadioFrequency/Parity",2);
    }
    if(config_map.contains("RadioFrequency/BaudRate")){
        config_map.insert("RadioFrequency/BaudRate",115200);
    }
    if(config_map.contains("RadioFrequency/DataBits")){
        config_map.insert("RadioFrequency/DataBits",8);
    }
    if(config_map.contains("RadioFrequency/StopBits")){
        config_map.insert("RadioFrequency/StopBits",1);
    }
}

void Configure::save()
{
    QSettings settings(config_file, QSettings::IniFormat);
    for (QMap<QString, QVariant>::iterator it = config_map.begin(); it != config_map.end(); ++it)
    {
        settings.setValue(it.key(), it.value());
    }
}

QVariant Configure::getValue(const QString &what)
{
    return config_map.value(what, QVariant());
}

void Configure::setValue(const QString &what, const QVariant &value)
{
    config_map.insert(what, value);
}
