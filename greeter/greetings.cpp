/*
 *
 * Copyright (C) 2001 Adrian Schroeter <adrian@suse.de>
 *
 */

#include <QWidget>
#include <QLayout>
#include <QCheckBox>
#include <QString>
#include <QSpinBox>
#include <QRegExp>
#include <QLabel>
#include <QLayout>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QDomDocument>
#include <QShowEvent>
#include <QScrollBar>

#include <KApplication>
#include <KConfig>
#include <KGlobal>
#include <KStandardDirs>
#include <KLocale>
#include <KCModule>
#include <KProcess>

#include "greetings.h"

/**** SUSEgreetings ****/

SUSEgreetings::SUSEgreetings()
// the Qt implementation is a bit broken, the frameless hint also disables
// closing of the window altogether, so add the close button hint in order
// to enable Alt+F4, and the button itself actually won't be shown with KWin anyway
     : QDialog ( 0, Qt::FramelessWindowHint | Qt::WindowCloseButtonHint )
{
     QFile f;
     QString content;

     // header
     QString filename = KStandardDirs::locate ( "data", "SUSEgreeter/greet_header.html" );
     f.setFileName ( filename );
     if ( ! f.open ( QIODevice::ReadOnly ) ) {
          // %1 = filename
          content = i18n ( "Error loading %1", QLatin1String ( "greet_header.html" ) );
     } else {
          QTextStream stream ( &f );
          content = stream.readAll();
          stream.reset();
          f.close();
     }

     // section template
     QString section_template;
     filename = KStandardDirs::locate ( "data", "SUSEgreeter/greet_section.html" );
     f.setFileName ( filename );
     if ( ! f.open ( QIODevice::ReadOnly ) ) {
          // %1 = filename
          section_template = i18n ( "Error loading %1", QLatin1String ( "greet_section.html" ) );
     } else {
          QTextStream stream ( &f );
          section_template = stream.readAll();
          stream.reset();
          f.close();
     }

     // sections
     filename = KStandardDirs::locate ( "data", "SUSEgreeter/greet.xml" );
     f.setFileName ( filename );
     if ( ! f.open ( QIODevice::ReadOnly ) ) {
          // %1 = filename
          content += i18n ( "Error loading %1", QLatin1String ( "greet.xml" ) );
     } else {
          QDomDocument doc ( "sections" );
          if ( !doc.setContent ( &f ) ) {
               content += i18n ( "Error loading %1", QLatin1String ( "greet.xml" ) );
          } else {
               QDomElement docElem = doc.documentElement();
               QDomNode n = docElem.firstChild();
               while ( !n.isNull() ) {
                    QDomElement e = n.toElement();
                    if ( !e.isNull() ) {
                         if ( e.tagName() =="section" ) {
                              QString section = section_template;
                              QDomNode ex = n.firstChild();
                              while ( !ex.isNull() ) {
                                   QDomElement e2 = ex.toElement();
                                   if ( !e2.isNull() ) {
                                        if ( e2.tagName() =="icon" ) {
                                             section.replace ( "__ICON__", e2.text() );
                                        } else if ( e2.tagName() =="title" ) {
                                             section.replace ( "__TITLE__", i18n ( e2.text().toAscii() ) );
                                        } else if ( e2.tagName() =="text" ) {
                                             section.replace ( "__TEXT__", i18n ( e2.text().toAscii() ) );
                                        }
                                   }
                                   ex = ex.nextSibling();
                              }
                              content += section;
                         }
                    }
                    n = n.nextSibling();
               }
          }
          f.close();
     }

     // footer
     filename = KStandardDirs::locate ( "data", "SUSEgreeter/greet_footer.html" );
     f.setFileName ( filename );
     if ( ! f.open ( QIODevice::ReadOnly ) ) {
          // %1 = filename
          content = i18n ( "Error loading %1", QLatin1String ( "greet_footer.html" ) );
     } else {
          QTextStream stream ( &f );
          content += stream.readAll();
          stream.reset();
          f.close();
     }
     content.replace ( "__ENJOY_OPENSUSE__", i18n ( "Have a lot of fun!" ) );
     content.replace ( "__CLOSE__", i18n ( "CLOSE" ) );
     content.replace ( "__INTRODUCTION__", i18n ( "Show Introduction to KDE" ) );
     setStyleSheet("background:transparent;");
     setAttribute(Qt::WA_TranslucentBackground);
     setWindowFlags(Qt::FramelessWindowHint);

     Text = new KTextBrowser ( this, "TextView" );     
     Text->setText ( content );
     Text->setNotifyClick ( true );
     Text->setFrameStyle ( QFrame::NoFrame );     
     QHBoxLayout *top = new QHBoxLayout ( this );
     top->setContentsMargins ( 0, 0, 0, 0 );
     top->addWidget ( Text );
     setFixedSize ( 800, 600 );
     top->activate();

     QFont font;
     font.setPixelSize ( 17 );
     font.setFamily ( "sans serif" );
     Text->setFont ( font );
     Text->adjustSize();

     top->activate();

     connect ( Text, SIGNAL ( urlClick ( const QString& ) ), this, SLOT ( urlClick ( const QString& ) ) );
}

void SUSEgreetings::showEvent ( QShowEvent* e )
{
     QDialog::showEvent ( e );

     adjustFontSize();
}

void SUSEgreetings::adjustFontSize()
{
     if ( Text->verticalScrollBar()->isVisible() ) {
          QFont font = Text->font();
          if ( font.pixelSize() < 14 )
               return;

          font.setPixelSize ( font.pixelSize()-1 );
          Text->setFont ( font );

          QTimer::singleShot ( 0, this, SLOT ( adjustFontSize() ) );
     }
}

SUSEgreetings::~SUSEgreetings()
{
}

void SUSEgreetings::urlClick ( const QString &s )
{
     // to get rid of const
     QString url ( s );

     if ( url.startsWith ( "/close" ) ) {
          kapp->quit();
          return;
     }

     if ( url=="http://software.opensuse.org/" )
          url="http://software.opensuse.org/search?baseproject=openSUSE%3A12.1";

     if ( url.startsWith ( "/you" ) ) {
          KProcess::startDetached ( "kdesu", QStringList() << "/sbin/yast2" << "online_update" );
     } else if ( url.startsWith ( "irc://" ) ) {
          KProcess::startDetached ( "konversationircprotocolhandler", QStringList() << url );
     } else if ( url.startsWith ( "/introduction" ) ) {
          url="http://userbase.kde.org/";
          KProcess::startDetached ( "kfmclient", QStringList() << "openURL" << url );
     } else {
          KProcess::startDetached ( "kfmclient", QStringList() << "openURL" << url );
     }

     // give the user some feedback
     QApplication::changeOverrideCursor ( Qt::WaitCursor );
     QTimer::singleShot ( 2000, this, SLOT ( resetCursor() ) );
};

void SUSEgreetings::resetCursor()
{
     QApplication::restoreOverrideCursor();
};

int SUSEgreetings::buttons()
{
     return 0 ;
}

QString SUSEgreetings::quickHelp() const
{
     return QString ( "" );
}

#include "greetings.moc"
