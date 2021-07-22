#include "principal.h"
#include "ui_principal.h"
#include <QtDebug>
#include <QFile>

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);

    // Se crea el lienzo

    lienzo = QPixmap(500,500);

    // Invocar al metodo dibujar

    this->dibujar();

    // Se muestra lienzo en el cuadro
    ui->Cuadro->setPixmap(lienzo);
}

Principal::~Principal()
{
    delete ui;
}

void Principal::dibujar()
{
    // Se rellana el lienzo de color blanco

  lienzo.fill(Qt::white);

    // Creamos el pincel, este trabaja sobre el objeto lienzo

    QPainter painter(&lienzo);

    // Definimos variables

    int x=50;
    int y=50;
    int ancho =  100;
    int alto_1 = ui->inNota1->value();
    int alto_2 = ui->inNota2->value();
    int alto_3 = ui->inNota3->value();

    // Creamos un pincel

    QPen pincel;    // Creamos el pincel
    pincel.setWidth(3); //Ancho del pincel
    pincel.setColor(Qt::red);   // Seleccionamos el color
    pincel.setJoinStyle(Qt::MiterJoin);

    // Establecer el pincel

    painter.setPen(pincel);
    int num = 100;
    for(int i=y; i<450; i+=100){
        painter.drawLine(x-25,i,x+5,i);
        QString linea = QString::number(num);
        painter.drawLine(x-5, i, y+410+5, i);
        linea = QString::number(num);
        painter.drawText(x-47,i,linea);
        num-=25;
    }
    QColor nota(87, 53, 78);
    pincel.setColor(nota);
    painter.setPen(pincel);
    for (int o=x; o<450; o+=100) {
        QString nota1 = "Nota 1 ";
        painter.drawText(x+25, y+415, nota1);
        QString nota2 = "Nota 2";
        painter.drawText(x+180, y+415, nota2);
        QString nota3 = "Nota 3";
        painter.drawText(x+340, y+415, nota3);
    }
    // Graficar barras

    // Crear colores para la 1 barra
    QPen pincel2;

    QColor colorBorde1(78,3,48);
    QColor colorRelleno1(201,176,255);

    pincel.setColor(colorBorde1);
    painter.setPen(pincel2);
    painter.setPen(pincel);
    painter.setBrush(colorRelleno1);

    // Dibujar la primera barra

    painter.drawRect(x,y+(400-alto_1),ancho, alto_1);

    // Crear colores para la 2 barra

    QColor colorBorde2 (78,3,48);
    QColor colorRelleno2(241,133,255);

    // Establecer el color al pincel

    pincel.setColor(colorBorde2);

    // Volver a establecer al objeto painter

    painter.setPen(pincel);

    // Establecer el color de la brocha

    painter.setBrush(colorRelleno2);

    // Dibujar la 2 barra

    painter.drawRect(x+150,y+(400-alto_2),ancho, alto_2);

    // Crear colores para la 3 barra

    QColor colorRelleno3 (74,231,255);
    QColor colorBorde3(78,3,48);

    // Establecer el color al pincel

    pincel.setColor(colorBorde3);

    // Sentamos el pincel

    painter.setPen(pincel);

    // Hacemos el relleno del color

    painter.setBrush(colorRelleno3);

    // Rellenamos con el color dado junto con las operaciones necesarias
    painter.drawRect(x+300,y+(400-alto_3), ancho, alto_3);

    ui->Cuadro->setPixmap(lienzo);
}


void Principal::on_cmdGraficar_released()
{
    dibujar();

}
// Cerramos el programa la opcion de salir

void Principal::on_actionSalir_triggered()
{
    this->close();
}

// Guardar como png
void Principal::on_actionGuardar_triggered()
{

    QString nombreArchivo = QFileDialog::getSaveFileName(
                this,"Guardar imagen",QString(),"Imagenes (*.png)");
    if (!nombreArchivo.isEmpty()){
        if (lienzo.save(nombreArchivo))
            QMessageBox::information(this,"Guardar imagen","Archivo guarado en: " + nombreArchivo);
        else
            QMessageBox::warning(this,"Guardar imagen","No se pudo guardar el archivo");
    }

}
