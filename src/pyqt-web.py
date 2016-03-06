import sys
from PyQt4.QtGui import QApplication
from PyQt4.QtCore import QUrl
from PyQt4.QtWebKit import QWebView


class Browser(QWebView):
    def __init__(self):
        QWebView.__init__(self)
        self.loadFinished.connect(self._result_available)

    def _result_available(self, ok):
        frame = self.page().mainFrame()
        print(frame.toHtml().encode('utf-8'))


if __name__ == '__main__':
    app = QApplication(sys.argv)
    view = Browser()
    view.load(QUrl("html/main.html"))
    view.setVisible(True)
    app.exec_()