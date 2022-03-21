#include "Universal.h"
#include "Window.h"
Window Win;

#define RGB888_RED      0x00ff0000
#define RGB888_GREEN    0x0000ff00
#define RGB888_BLUE     0x000000ff

#define RGB565_RED      0xf800
#define RGB565_GREEN    0x07e0
#define RGB565_BLUE     0x001f

unsigned short RGB888toRGB565(unsigned int n888Color) {
	unsigned short n565Color = 0;

	//获取RGB单色并截取高位;
	unsigned char cRed = (n888Color & RGB888_RED) >> 19;
	unsigned char cGreen = (n888Color & RGB888_GREEN) >> 10;
	unsigned char cBlue = (n888Color & RGB888_BLUE) >> 3;

	//拼接;
	n565Color = (cRed << 11) + (cGreen << 5) + (cBlue << 0);
	return n565Color;
}

int main() {
	cout << "<RGB888 to RGB565>\n" << endl;
	string ImgPath = ""; cout << "将要转换的图片托到此处: "; cin >> ImgPath;
	string Add = ""; cout << "输出十六进制值首是否添加'0x'(1/0): "; cin >> Add;

	Win.Initialize_Window(64, 64, EW_SHOWCONSOLE);
	loadimage(NULL, ImgPath.c_str(), 0, 0, true);
	//ImageSize;
	int IMGWidth = Win.GetWidth(); int IMGHeight = Win.GetHeight(); int IMGSize = IMGWidth * IMGHeight;

	//准备输出的文件;
	ofstream location_out;
	location_out.open("To_RGB565_Out.txt", std::ios::out | std::ios::app);

	char **HEX_RGB565 = new char *[IMGSize] {NULL};
	string Str_RGB565 = "";

	int x = 0, y = 0; for (int i = 0; i < IMGSize; ++i) {
		HEX_RGB565[i] = new char[4];//初始化用于容纳单个16进制数的数组;
		itoa(RGB888toRGB565(getpixel(x, y)), HEX_RGB565[i], 16);//转为16进制数;

		if (Add != "0") { Str_RGB565 = Str_RGB565 + "0x" + HEX_RGB565[i] + ","; } else { Str_RGB565 = Str_RGB565 + HEX_RGB565[i] + ","; }

		if (x >= IMGWidth) { ++y; x = 0; } else { putpixel(x, y, RGB(85, 177, 85)); ++x; }
		if (y >= IMGHeight) { break; }
	}closegraph(); system("cls");

	cout << Str_RGB565 << endl;
	location_out << Str_RGB565 << endl; location_out.close();
	cout << "\n>>已导出色彩文件(请在本程序根目录下查找)\n" << endl;

	system("pause");
}