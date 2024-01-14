#include "widget.h"
#include "ui_widget.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>
/**
 * @brief Widget::Widget
 *反序列化就是将JSON字符串中的数据取出来
 * fromBytearryData是处理二进制JSON字符串，fromJSON处理的是文本格式的JSON字符串
 * 1.读取JSON文件，得到字符串2.通过QJsonDocument这个类提供的静态方法（fromJson或fromBytearryData，将读到的字符串转换成QJsonDocument类型的字符串或类
 * 3.通过isArry或isObject方法进行判断是数组还是类4.通过object或array将对象或数组取出
 * @param parent
 */
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QJsonDocument doc;
    if(doc.isEmpty())
    {
        qDebug()<<"doc is empty";
    }
    if(doc.isNull())
    {
        qDebug()<<"doc is null";
    }
    writeJson();
    readJson();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::writeJson()
{
    QJsonObject obj;
    obj.insert("name","ACE");
    obj.insert("sex","man");
    obj.insert("age",20);

    QJsonObject subObj;
    subObj.insert("father","gal");
    subObj.insert("mother","lily");

    QJsonArray array;
    array.append("monkey");
    array.append("chicken");
    array.append("cat");

    subObj.insert("brother",array);
    obj.insert("family",subObj);
    obj.insert("isAlive",false);
    obj.insert("comment","yyds");

    QJsonDocument doc(obj);
    QByteArray json = doc.toJson();

    QFile file("D:\\ace.json");
    file.open(QIODevice::WriteOnly);
    if(!file.isOpen())
    {
        qDebug()<<"open filed";
    }
    file.write(json);
    file.close();

}

void Widget::readJson()
{
    QFile file("D:\\ace.json");
    if(!file.open(QIODevice::ReadWrite))
    {
        qDebug()<<"open error";
    }
    QByteArray byteArry = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(byteArry);
    QJsonObject obj = doc.object();
    QStringList keys = obj.keys();
    for(int i=0;i<keys.size();i++)
    {
        QString key = keys.at(i);
        QJsonValue value = obj.value(key);
        if(value.isBool())
        {
            qDebug()<<value.toBool();
        }else if(value.isString())
        {
            qDebug()<<value.toString();
        }else if(value.isDouble())
        {
            qDebug()<<value.toInt();
        }else if(value.isObject())
        {
            QJsonObject subJaon = value.toObject();
            QStringList subkeys = subJaon.keys();
            for(int k=0;k<subkeys.size();k++)
            {
                QJsonValue subValue = subJaon.value(subkeys.at(k));
                if(subValue.isString())
                {
                    qDebug()<<subValue.toString();
                }else if(subValue.isArray())
                {
                    QJsonArray arry = subValue.toArray();
                    for(int j=0;j<arry.size();j++)
                    {
                        qDebug()<<arry[j].toString();
                    }
                }

            }
        }
    }
//    QFile file("D:\\ace.json");
//    file.open(QFile::ReadOnly);
//    QByteArray all = file.readAll();
//    file.close();
//    QJsonDocument doc = QJsonDocument::fromJson(all);
//    QJsonObject obj = doc.object();
//    QStringList keys = obj.keys();
//    for(int i=0;i<keys.size();i++)
//    {
//        QString key = keys.at(i);
//        QJsonValue value = obj.value(key);
//        if(value.isBool())
//        {
//            qDebug()<<key <<":"<<value.toBool();
//        }
//        else if(value.isString())
//        {
//            qDebug()<<key<<":"<<value.toString();
//        }
//        else if(value.isDouble())
//        {
//            qDebug()<<key<<":"<<value.toInt();
//        }else if(value.isObject())
//        {
//            qDebug()<<key<<":";
//            QJsonObject subObj = value.toObject();
//            QStringList subkeys = subObj.keys();
//            for(int k=0;k<subkeys.size();k++)
//            {
//                QJsonValue subValue = subObj.value(subkeys.at(k));
//                if(subValue.isString())
//                {
//                    qDebug()<<" " <<subkeys.at(k) <<":" <<subValue.toString();
//                }
//                else if(subValue.isArray())
//                {
//                    QJsonArray array = subValue.toArray();
//                    for(int j=0;j<array.size();j++)
//                    {
//                        qDebug()<<" " <<array[j].toString();
//                    }

//                }
//            }
//        }
//    }
}

