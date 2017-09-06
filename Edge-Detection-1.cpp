/*Programmer Name-Anish Niranjan Hemmady.Multimedia Project-Edge detection
*/
#define _CRT_SECURE_NO_DEPRECATE
#include <conio.h>
#include <stdio.h>
#include<iostream>
#include<cmath>

//class point to represent single pixel value and its index
class Point{
public:
	double value;
	int indx;
};
//class Image to read pixel location and its value
class Image

{
public:
	unsigned char *inp_arry;
	int width;
	Image(unsigned char* inp_arry, int width);
	//row major order principle used
	Point image(int x, int y){
		int indx = (x*width + y);
		Point pt;
		pt.value=inp_arry[indx];
		pt.indx = indx;
		return pt;
	}
	~Image();
private:

};
//constructor
Image::Image(unsigned char *inp_arry, int width)
{
	this->inp_arry = inp_arry;
	this->width = width;
}
//destructor
Image::~Image()
{
}
//main edge detection class
class Edge_detectn{
public:
	//finding gradient in x and y direction
	void grad_x_y(unsigned char* inp_arry, int width, int height){
		//sobel operator for Gx
		//use this same Gx just change x and y location while accessing it to get sobel for Gy.i.e Transpose of Gx
		int sobel[3][3] = { { 1, 0, -1 }, { 2, 0, -2 }, { 1, 0, -1 } };
		unsigned char * grdx = new unsigned char [width*height];
		for (int m = 0; m < width*height; m++){
			grdx[m] = 0;
		}
		unsigned char * grdy = new unsigned char[width*height];
		for (int m = 0; m < width*height; m++){
			grdy[m] = 0;
		}
		Image  img(inp_arry,width);
		int sobel_rows = sizeof(sobel) / sizeof(sobel[0]);
		int sobel_cols = sizeof(sobel[0]) / sizeof(int);
		for (int i = 1; i <= height - 1; i++){
			for (int j = 1; j <=width - 1; j++){
				
				double sum = 0;
				//std::cout << pnt.indx << "-->" << pnt.value;
				//inp_arry[pnt.indx+1] = pnt.value;
				for (int y = 0; y < sobel_rows; y++){
					for (int x = 0; x < sobel_cols; x++){
						Point pnt = img.image(y+i-1, x+j-1);
						double tmp = pnt.value*sobel[x][y];
						sum += tmp;
					}
					
				}
				Point pnt = img.image(i, j);
				sum = (sum / 4.0) + 128.0;
				grdx[pnt.indx] = (unsigned char)sum;
				
			}
		}
		//sobel y
		for (int i = 1; i <= height - 1; i++){
			for (int j = 1; j <= width - 1; j++){

				double sum = 0;
				//std::cout << pnt.indx << "-->" << pnt.value;
				//inp_arry[pnt.indx+1] = pnt.value;
				for (int y = 0; y < sobel_rows; y++){
					for (int x = 0; x < sobel_cols; x++){
						Point pnt = img.image(y + i - 1, x + j - 1);
						double tmp = pnt.value*sobel[y][x];
						sum += tmp;
					}

				}
				Point pnt = img.image(i, j);
				sum = (sum / 4.0) + 128.0;
				grdy[pnt.indx] = (unsigned char)sum;

			}
		}
		FILE *fw = fopen("grdx.raw", "wb");
		fwrite(grdx, (height*width), sizeof(unsigned char), fw);
		fclose(fw);
		FILE *fw2 = fopen("grdy.raw", "wb");
		fwrite(grdy, (height*width), sizeof(unsigned char), fw2);
		fclose(fw2);


	}
	//for 5*5 sobel find gradient
	void grad_x_y_55(unsigned char* inp_arry, int width, int height){
		////use this same Gx just change x and y location while accessing it to get sobel for Gy.i.e Transpose of Gx
		int sobel[5][5] = { { -1, -2, 0, 2, 1 }, { -2, -4, 0, 4, 2 }, { -4, -8, 0, 8, 4 }, { -2, -4, 0, 4, 2 }, { -1, -2, 0, 2, 1 } };
		unsigned char * grdx_55 = new unsigned char[width*height];
		for (int m = 0; m < width*height; m++){
			grdx_55[m] = 0;
		}
		unsigned char * grdy_55 = new unsigned char[width*height];
		for (int m = 0; m < width*height; m++){
			grdy_55[m] = 0;
		}
		Image  img(inp_arry, width);
		int sobel_rows = sizeof(sobel) / sizeof(sobel[0]);
		int sobel_cols = sizeof(sobel[0]) / sizeof(int);
		for (int i = 1; i <= height - 1; i++){
			for (int j = 1; j <= width - 1; j++){

				double sum = 0;
				//std::cout << pnt.indx << "-->" << pnt.value;
				//inp_arry[pnt.indx+1] = pnt.value;
				for (int y = 0; y < sobel_rows; y++){
					for (int x = 0; x < sobel_cols; x++){
						Point pnt = img.image(y + i - 1, x + j - 1);
						double tmp = pnt.value*sobel[x][y];
						sum += tmp;
					}

				}
				Point pnt = img.image(i, j);
				sum = (sum / 10.0) + 128.0;
				grdx_55[pnt.indx] = (unsigned char)sum;

			}
		}
		//sobel y
		for (int i = 1; i <= height - 1; i++){
			for (int j = 1; j <= width - 1; j++){

				double sum = 0;
				//std::cout << pnt.indx << "-->" << pnt.value;
				//inp_arry[pnt.indx+1] = pnt.value;
				for (int y = 0; y < sobel_rows; y++){
					for (int x = 0; x < sobel_cols; x++){
						Point pnt = img.image(y + i - 1, x + j - 1);
						double tmp = pnt.value*sobel[y][x];
						sum += tmp;
					}

				}
				Point pnt = img.image(i, j);
				sum = (sum / 10.0) + 128.0;
				grdy_55[pnt.indx] = (unsigned char)sum;

			}
		}
		FILE *fw = fopen("grdx55.raw", "wb");
		fwrite(grdx_55, (height*width), sizeof(unsigned char), fw);
		fclose(fw);
		FILE *fw2 = fopen("grdy55.raw", "wb");
		fwrite(grdy_55, (height*width), sizeof(unsigned char), fw2);
		fclose(fw2);


	}
	//find magnitude for 3*3 sobel operator over Gx33 and Gy33
	void mag(unsigned char *inpx,unsigned char *inpy,int width,int height){
		unsigned char * magn = new unsigned char[width*height];
		for (int m = 0; m < width*height; m++){
			magn[m] = 0;
		}
		Image imgx(inpx, width);
		Image imgy(inpy, width);
		for (int i = 0; i < height; i++){
			for (int j = 0; j < width; j++){
				Point pntx = imgx.image(i, j);
				Point pnty = imgy.image(i, j);
				double x_val = pntx.value;
				double y_val = pnty.value;
				x_val -= 128;
				y_val -= 128;
				double sqrd = pow(x_val, 2) + pow(y_val, 2);
				double ans = sqrt(sqrd);
				magn[pntx.indx] = (unsigned char)ans;
			}
		}
		FILE *fm = fopen("magn.raw", "wb");
		fwrite(magn, (height*width), sizeof(unsigned char), fm);
		fclose(fm);

	}
	//magnitude 5*5 sobel operator.Gx55 and Gy55 input
	void mag55(unsigned char *inpx, unsigned char *inpy, int width, int height){
		unsigned char * magn55 = new unsigned char[width*height];
		for (int m = 0; m < width*height; m++){
			magn55[m] = 0;
		}
		Image imgx(inpx, width);
		Image imgy(inpy, width);
		for (int i = 0; i < height; i++){
			for (int j = 0; j < width; j++){
				Point pntx = imgx.image(i, j);
				Point pnty = imgy.image(i, j);
				double x_val = pntx.value;
				double y_val = pnty.value;
				x_val -= 128;
				y_val -= 128;
				double sqrd = pow(x_val, 2) + pow(y_val, 2);
				double ans = sqrt(sqrd);
				magn55[pntx.indx] = (unsigned char)ans;
			}
		}
		FILE *fm1 = fopen("magn55.raw", "wb");
		fwrite(magn55, (height*width), sizeof(unsigned char), fm1);
		fclose(fm1);

	}
	//finding threshold for bot 5*5 and 3*3
	void threshld(unsigned char *mgn, int width, int height){
		double Threshold = 30;
		double set_whte = 255;
		double set_blck = 0.0;
		unsigned char * thresh = new unsigned char[width*height];
		for (int m = 0; m < width*height; m++){
			thresh[m] = 0;
		}
		Image th(mgn, width);
		for (int i = 0; i < height; i++){
			for (int j = 0; j < width; j++){
				//since it should be one pixel wide check its 4 neighbors and do hysterisis thresholding
				Point thpnt1 = th.image(i, j);
				Point thpnt2 = th.image(i - 1, j);
				Point thpnt3 = th.image(i + 1, j);
				Point thpnt4 = th.image(i, j - 1);
				Point thpnt5 = th.image(i, j + 1);
				if ((thpnt1.value>thpnt4.value) && (thpnt1.value>thpnt5.value) && (thpnt1.value>Threshold) || (thpnt1.value<thpnt2.value) && (thpnt1.value<thpnt3.value) && (thpnt1.value<-Threshold)){
					thresh[thpnt1.indx] = (unsigned char)set_whte;
				}
				else{
					thresh[thpnt1.indx] = (unsigned char)set_blck;
				}
			}
		}
		FILE *fwth = fopen("threshlded.raw", "wb");
		fwrite(thresh, (height*width), sizeof(unsigned char), fwth);
		fclose(fwth);
			
	}


};
int main(){
	Edge_detectn edg;
	const int rows = 312;
	const int columns = 500;
	unsigned char img_data[rows*columns];
	unsigned char gradnt_x[rows*columns];
	unsigned char gradnt_y[rows*columns];
	unsigned char gradnt_x_55[rows*columns];
	unsigned char gradnt_y_55[rows*columns];
	unsigned char magnitude[rows*columns];
	FILE *fp,*fx,*fy,*fm,*fx1,*fy1;
	fp = fopen("IMG1.raw", "rb");
	if (!fp){
		printf("ERROR");
	}
	fread(img_data, rows*columns, sizeof(unsigned char), fp);
	edg.grad_x_y(img_data,columns,rows);
	edg.grad_x_y_55(img_data, columns, rows);
	fx =fopen("grdx.raw", "rb");
	if (!fx){
		printf("ERROR");
	}
	fread(gradnt_x, rows*columns, sizeof(unsigned char), fx);
	fy = fopen("grdy.raw", "rb");
	if (!fy){
		printf("ERROR");
	}
	fread(gradnt_y, rows*columns, sizeof(unsigned char), fy);
	edg.mag(gradnt_x, gradnt_y, columns,rows);
	fx1 = fopen("grdx55.raw", "rb");
	if (!fx1){
		printf("ERROR");
	}
	fread(gradnt_x_55, rows*columns, sizeof(unsigned char), fx1);
	fy1 = fopen("grdy55.raw", "rb");
	if (!fy1){
		printf("ERROR");
	}
	fread(gradnt_y_55, rows*columns, sizeof(unsigned char), fy1);
	edg.mag55(gradnt_x_55, gradnt_y_55, columns, rows);
	fm = fopen("magn55.raw", "rb");
	if (!fm){
		printf("ERROR");
	}
	fread(magnitude, rows*columns, sizeof(unsigned char), fm);
	edg.threshld(magnitude,columns,rows);


	getchar();
}




