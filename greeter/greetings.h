#include <QShowEvent>
/* vi: ts=8 sts=4 sw=4
 */

#ifndef __greetings_h_included__
#define __greetings_h_included__

class KConfig;

#include <QDialog>
#include <QLabel>
#include <QImage>
#include <KTextBrowser>


class SUSEgreetings : public QDialog {
     Q_OBJECT

public:
     SUSEgreetings();
     ~SUSEgreetings();

     int buttons();
     QString quickHelp() const;

protected:
     void showEvent ( QShowEvent* );

protected slots:
     void urlClick ( const QString& );
     void adjustFontSize();
     void resetCursor();

private:
     KTextBrowser *Text;
};

#endif
