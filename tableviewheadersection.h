#ifndef TABLEVIEWHEADERSECTION
#define TABLEVIEWHEADERSECTION

#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <QHeaderView>
#include <QPointer>
#include <QPainter>



class TableViewHeaderWidget : public QWidget
{
public:
    QLabel *headerLable;
    QLineEdit *headerLE;
    QComboBox *headerCB;
    TableViewHeaderWidget(QWidget *parent = 0) : QWidget(parent)
    {
        headerLable = new QLabel(this);
        headerLE = new QLineEdit(this);
        headerCB = new QComboBox(this);
        QVBoxLayout *vl = new QVBoxLayout(this);
        vl->addWidget(headerLable, 1, Qt::AlignCenter);
        vl->addWidget(headerLE);
        vl->addWidget(headerCB);
        setLayout(vl);
    }
};


class TableViewHeaderSection : public QHeaderView
{
    Q_OBJECT

public:
    explicit TableViewHeaderSection(int colCount, QWidget* parent):QHeaderView(Qt::Horizontal, parent)
    {
        columnCount = colCount;
        for(int i = 0; i < columnCount; i++)
        {
            headerSections.insert(i,new TableViewHeaderWidget(this));
            headerSections[i]->headerCB->setFixedHeight(30);
            headerSections[i]->headerLE->setFixedHeight(30);
            connect(headerSections[i]->headerLE, SIGNAL(textChanged(QString)),this,SIGNAL(sectionsWidgetsSignal()) );
            connect(headerSections[i]->headerCB, SIGNAL(currentIndexChanged(int)),this, SIGNAL(sectionsWidgetsSignal()));
        }
    }

    void setHeaderSectionLable(int section, QString label)
    {
        headerSections[section]->headerLable->setText(label);
    }

    void setSectionWidth(int section, int width)
    {
        headerSections[section]->headerLable->setFixedWidth(width);
        headerSections[section]->headerCB->setFixedWidth(width);
    }

    void HideHeaderSectionWidgets(int section)
    {
        headerSections[section]->headerLable->setEnabled(false);
        headerSections[section]->headerLable->hide();
        headerSections[section]->headerCB->setEnabled(false);
        headerSections[section]->headerCB->hide();
        headerSections[section]->headerLE->setEnabled(false);
        headerSections[section]->headerLE->hide();
    }

    void hideHeaderSectionLabel(int section){headerSections[section]->headerLable->setEnabled(false);headerSections[section]->headerLable->hide();}

    void hideHeaderSectionLE(int section){headerSections[section]->headerLE->setEnabled(false);headerSections[section]->headerLE->hide();}

    void hideHeaderSectionCB(int section){headerSections[section]->headerCB->setEnabled(false);headerSections[section]->headerCB->hide();}

    void resetHeaderWidgets()
    {
        for(int i =0; i < columnCount; i++)
        {
            headerSections[i]->headerLE->clear();
            headerSections[i]->headerCB->setCurrentIndex(headerSections[i]->headerCB->findData(0));
        }
    }

    QString getHeaderLEText(int section){return headerSections[section]->headerLE->text();}

    QVariant getHeaderCBCurrentData(int section){return headerSections[section]->headerCB->currentData();}

    QString getHeaderCBCurrentText(int section)
    {
        if(headerSections[section]->headerCB->currentData().toInt() == 0)//all
            return "";
        else
            return headerSections[section]->headerCB->currentText();
    }

    void showHeaderSectionLabel(int section){headerSections[section]->headerLable->setEnabled(true);headerSections[section]->headerLable->show();}

    void showHeaderSectionLE(int section){headerSections[section]->headerCB->setEnabled(true);headerSections[section]->headerCB->show();}

    void showHeaderSectionCB(int section){headerSections[section]->headerLE->setEnabled(true);headerSections[section]->headerLE->show();}

    void setLEAlignment(int section, Qt::Alignment alignment){headerSections[section]->headerLE->setAlignment(alignment);}

    void setLEPlaceHolder(int section, QString PH){headerSections[section]->headerLE->setPlaceholderText(PH);}

    void setLEText(int section, QString data){headerSections[section]->headerLE->setText(data);}

    void setCBCurrentData(int section, QVariant data){headerSections[section]->headerCB->setCurrentIndex(headerSections[section]->headerCB->findData(data));}

    void addCBItem(int section, const QString text, const QVariant data){headerSections[section]->headerCB->addItem(text, data);}

    void setCBLayoutDirection(int section, Qt::LayoutDirection direction){headerSections[section]->headerCB->setLayoutDirection(direction);}

    QSize sizeHint() const
    {
        QSize s = size();
        s.setHeight(headerSections[4]->minimumSizeHint().height()+5);
        s.setWidth(headerSections[4]->minimumSizeHint().width()+5);
        return s;
    }

signals:
    void sectionsWidgetsSignal();

protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
    {
        QPainterPath path;
        path.addRect(rect);
        painter->fillPath(path,QBrush(QColor(220,220,230)));
        painter->drawRect(rect);
        if (!rect.isValid())
            return;
        headerSections[logicalIndex]->setGeometry(rect);
        headerSections[logicalIndex]->show();
    }

private:
    QVector< QPointer<TableViewHeaderWidget> > headerSections; //vector of pointers to our widgets
    int columnCount;

};


#endif // TABLEVIEWHEADERSECTION

