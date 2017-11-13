/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Die Mai 22 17:24:18 CEST 2001
    copyright            : (C) 2001 by Ralf Nolden
    email                : nolden@kde.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

//#include "config.h"
#include <KCmdLineArgs>
#include <K4AboutData>
#include <KLocale>
#include <greetings.h>
#include <QDesktopWidget>

#include <KGlobal>
#include <KRun>
#include <KApplication>
#include <KConfig>
#include <KConfigGroup>

int main ( int argc, char *argv[] )
{

     K4AboutData aboutData ( "SUSEgreeter", 0, ki18n ( "SUSEgreeter" ), "0.1",
                            ki18n ( "SUSEgreeter" ), K4AboutData::License_GPL, ki18n ( "(c) 2001, Adrian Schroeter" ) );
     aboutData.addAuthor ( ki18n ( "Adrian Schroeter" ), KLocalizedString(), "adrian@suse.de" );

     KCmdLineArgs::init ( argc, argv, &aboutData );

     //KLocale::setMainCatalog ( "SUSEgreeter" );

     KApplication a;

     KGlobal::locale()->insertCatalog ( QString::fromLatin1 ( "kpersonalizer" ) );

     // first, reset the startup from true (see desktop file in share/autostart) to false
     KConfig SUSEgreeterrc ( "SUSEgreeterrc" );
     KConfigGroup grp = SUSEgreeterrc.group ( "General" );
     bool ktip = ( grp.readEntry ( "FirstLogin113", true ) );
     grp.writeEntry ( "FirstLogin113", false );
     grp.sync();

     SUSEgreetings greeter;
     a.setTopWidget ( &greeter );
     greeter.adjustSize();

     QDesktopWidget *dsk = kapp->desktop();
     QRect scr = dsk->screenGeometry ( dsk->screenNumber ( QPoint ( 0, 0 ) ) );
     QRect grt ( 0, 0, greeter.width(), greeter.height() );
     grt.moveCenter ( scr.center() );
     greeter.setGeometry ( grt );
     greeter.show();

     int ret = a.exec();
     if ( ktip ) { // only run if we set this to true in the constructor. then SUSEgreeter didn't run before
          // set the ktiprc file entry to true. The global one is set to false for starting SUSEgreeter
#if 0
          KConfig ktiprc ( "ktiprc" );
          KConfigGroup group = ktiprc.group ( "TipOfDay" );
          group.writeEntry ( "RunOnStart", true );
          ktiprc.sync();
#endif

//      kapp->dcopClient()->send("kicker", "kicker", "showKMenu()", "");
     }
     return ret;
}
