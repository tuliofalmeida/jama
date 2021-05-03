#include <QString>
#include <QtTest>

class MatrixLongDoubleTest : public QObject
{
    Q_OBJECT

public:
    MatrixLongDoubleTest();

private Q_SLOTS:
    void testCase1();
};

MatrixLongDoubleTest::MatrixLongDoubleTest()
{
}

void MatrixLongDoubleTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(MatrixLongDoubleTest)

#include "tst_matrixlongdoubletest.moc"
