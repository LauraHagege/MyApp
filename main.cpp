#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <iostream>
#undef UNICODE
#undef _UNICODE
#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmimgle/dcmimage.h>
#include <QPixmap>
#include <QLabel>
#include <QVBoxLayout>

using namespace std;

int main(int argc, char *argv[])
{
    //QApplication app(argc, argv);


    //const char *file = "C:\\Users\\simms\\Desktop\\Laura\\DicomImg\\serie1\\image-000001.dcm";
    const char *file = "C:\\Users\\simms\\Desktop\\Laura\\CTAbdomen\\DICOMDAT\\SDY00000\\SRS00000\\IMG00000";
    DicomImage *image = new DicomImage(file);

   // QWidget window;

   // QLabel *layout=new QLabel;


    /*if (image != NULL){
        std::cout << "File found";
    }

    DcmFileFormat fileformat;
       OFCondition status = fileformat.loadFile(file);
       if (status.good())
       {
          OFString patientsName;
          if (fileformat.getDataset()->findAndGetOFString(DCM_PatientName, patientsName).good())
          {
             cout << "Patient's Name: " << patientsName << endl;
             cout << "Statu:" << image->getStatus() << endl ;
             cout << "Width:" << image->getWidth() << endl ;
             cout << "Monochrome:" << image->isMonochrome() << endl ;
             const DiPixel *pixeldata = image->getInterData();

          }else{
             cerr << "Error: cannot access Patient's Name!" << endl;
          }

       }else{
          cerr << "Error: cannot read DICOM file (" << status.text() << ")" << endl;
       }
       return 0;
*/


    if (image != NULL)
        {
          if (image->getStatus() == EIS_Normal)
          {
            Uint8 *pixelData = (Uint8 *)(image->getOutputData(8 )); // bits per sample
            // Uint8 is a pointer to internal memory buffer
            if (pixelData != NULL)
            {
                // do something useful with the pixel data
                //QImage img(pixelData,image->getWidth(), image->getHeight(), QImage::Format_Indexed8 );
                QColor color;
                QImage *img;
                void *pDicomDibits;
                uchar *px;
               // uchar pixel[4];
                const int width = (int)(image->getWidth());
                const int height = (int)(image->getHeight());
                if (image->isMonochrome()){
                    img = new QImage(width, height, QImage::Format_Indexed8);
                    img->setColorCount(256);
                    // define gray palette here
                    for (int i=0; i<256; i++) {
                        color.setRgb(i, i, i);
                        img->setColor(i, color.rgb());
                    }

                    image->createWindowsDIB(pDicomDibits, 0, 0, 8, 0, 1);
                    unsigned char * pd;
                    pd=(unsigned char *)pDicomDibits;

                    for (int y=0; y < (long) height; y++)
                    {
                        px = img->scanLine(y);
                        for (int x=0; x < (long) width; x++)
                        {
                            px[x] = (unsigned char) (*pd);
                            pd++;
                        }
                    }

                }else
                    cout << "Non monochrome image" << endl;

                img->save("C:\\Users\\simms\\Desktop\\Laura\\test.bmp");
            }
          } else
            cerr << "Error: cannot load DICOM image (" << DicomImage::getString(image->getStatus()) << ")" << endl;
        }
        //delete image;

    //window.show();

   // return app.exec();


}
