#include <QtXml>

#include "frmreports.h"
#include "globaldefs.h"

FrmReports::FrmReports(QWidget *parent, Qt::WFlags flags):
QWidget(parent, flags){

    setupUi(this);

     connect(pushClose, SIGNAL(clicked()), this,
    SIGNAL(hideFrmReports()),Qt::UniqueConnection);
}

FrmReports::~FrmReports()
{

}

void FrmReports::showEvent ( QShowEvent * event )
{
    this->frame->hide();
    listWidget->clear();
    if (!readReportNames ()) emit showError(tr("Could not parse reports directory!"));;
}

bool FrmReports::readReportNames ()
{
    QDir reportsDir;
    reportsDir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    reportsDir.setSorting(QDir::Size | QDir::Reversed);

     QStringList filters;
     filters << tr("*.bdrt");
     reportsDir.setNameFilters(filters);

    if (reportsDir.exists(qApp->translate("dir", strReportsDir)))
        reportsDir=QDir(qApp->translate("dir", strReportsDir));
    else return false;

    if (!reportsDir.isReadable()) return false;

    QFileInfoList list = reportsDir.entryInfoList(filters,QDir::Files,QDir::Name);
     for (int i = 0; i < list.size(); ++i) {
         QFileInfo fileInfo = list.at(i);
         listWidget->addItem(fileInfo.baseName());
     }

    return true;
}

void FrmReports::previewItem(QListWidgetItem* item)
{
    QString strName, strAuthor,strPixmap,strDescription;
    if (!parseXMLFile(item->text(),strName,strAuthor,strPixmap,strDescription)){
        emit showError(tr("Could not preview this item!"));
    }else{

        //TODO: add label for name and code herer
        if (!strAuthor.isEmpty()) 
            this->lbAuthor->setText(strAuthor);
        else 
        this->lbAuthor->setText(qApp->translate("empty", strEmpty));
        if (!strPixmap.isEmpty()){
            QPixmap pm;
            if (!pm.loadFromData(QByteArray::fromBase64(strPixmap.toAscii())) || pm.isNull())
                this->lbPixmap->setText(qApp->translate("empty", strEmpty));
            else
                this->lbPixmap->setPixmap(pm);
        }
        else 
            this->lbPixmap->setText(qApp->translate("empty", strEmpty));
        if (!strDescription.isEmpty())
            this->textDescription->setText(strDescription);
        else
            this->textDescription->setText(qApp->translate("empty", strEmpty));

        if (!frame->isVisible())
            frame->show();
    }
}

bool FrmReports::parseXMLFile(const QString itemName, QString& strName, QString& strAuthor, QString& strPixmap, QString& strDescription)
{
    QString strFileName(qApp->translate("dir", strReportsDir) + tr("\\") + itemName + tr(".bdrt"));

    QFile file(strFileName);
    if (!file.exists()) return false;
    if (!file.open(QFile::ReadOnly | QFile::Text)) return false;

    //Just try to parse the xml
    QXmlSimpleReader xmlReader;
    QXmlInputSource *source = new QXmlInputSource(&file);
    if (!xmlReader.parse(source)) {file.close(); return false;}//exit, but close the file first!
    delete source;

    file.close();

     //Initialize the reader
    if (!file.open(QFile::ReadOnly | QFile::Text)) return false;
    QXmlStreamReader xml(&file);

    if (!readProperties(xml, strName, strAuthor, strPixmap, strDescription)) return false;

    file.close();

    return true;
}


bool FrmReports::readProperties(QXmlStreamReader& xml, QString& strName, QString& strAuthor, QString& strPixmap, QString& strDescription)
{
    xml.readNextStartElement();
    xml.readNextStartElement();

    int ct=0;
    if (xml.name().toString()!=tr("properties") || !xml.isStartElement()) return false;
    while (!xml.isEndDocument() && !xml.hasError() && ct<5){
        xml.readNext();
        if (xml.isStartElement()){

            ct++;
            if (xml.name().toString()==tr("name")) strName=xml.readElementText();
            else if (xml.name().toString()==tr("author")) strAuthor=xml.readElementText();
            else if (xml.name().toString()==tr("icon")) strPixmap=xml.readElementText();
            else if (xml.name().toString()==tr("description")) strDescription=xml.readElementText();
            else ct--;

            /*
            if (xml.name().toString()==tr("queries") || xml.name().toString()==tr("menus"))
                xml.skipCurrentElement();
            else{
                qDebug() << xml.name().toString() << endl;
                qDebug() << xml.readElementText() << endl;
            }*/

        }
     }

    /*
    while (!xml.isEndDocument() && !xml.hasError() ){
        xml.readNext();
                tableList << xml.attributes().value(tr("name")).toString();
                xml.skipCurrentElement();
        }
    }
*/
    return true;
}