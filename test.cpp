﻿#include "Image_Class.h"
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
/*
+-----------+-----------+-----------+
|                NAME                 |      ID      |                      Work Breakdown                               |
+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+--------------+
|   Ahmed Bakr Abd El Hafez Muhammad  |     No ID    |   Grayscale - Resize - Crop - Frame - Warm (Bouns)                |
+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+--------------+
|   Muhammad Reda Abd El Nabi         |   20240497   |   Blur - Inverted - Darken and lighten - Merge - Purple (Bouns)   |
+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+--------------+
|   Youssef Osama Samy Azmy           |     No ID    |   Black & White - Flip - Rotate - Detect image - Infrared (Bouns) |
+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+--------------+
Section: Monday → Slot 12:45-2:15 → Lab5 → S17
The Link of The Repositories : redacoder005/Project-image
The Link of The Shared Documents : https://drive.google.com/file/d/1WqlvBGPct8b38dFvuU2WG18nWhAg005e/view?usp=drive_link
Video Link : https://drive.google.com/file/d/1jCTm-OJkIaNzAaZhHto6cO1SFYm_AIa0/view?usp=drive_link
--------------------------------------------
Description:
    This file contains multiple image processing filters
    implemented in C++. Each function applies a specific
    transformation to an input image such as grayscale,
    black & white, inversion, rotation, cropping, merging,
    and other effects.

    The filters use the Image_Class.h library to handle
    pixel manipulation, image loading, and saving.

    This file is part of the Image Filter Project.
-------------------------------------------------------------
*/

// Grayscale filter
void grey_filter(Image& image) {
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            unsigned int avg = 0;

            avg += image(x, y, 0); // Red
            avg += image(x, y, 1); // Green
            avg += image(x, y, 2); // Blue

            avg /= 3;

            for (int c = 0; c < 3; ++c) {
                image(x, y, c) = avg;
            }
        }
    }
    cout << "Grayscale filter applied successfully." << endl;
}

// Inverted filter
void inverted_filter(Image& image) {
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            for (int c = 0; c < 3; ++c) {
                image(x, y, c) = 255 - image(x, y, c);
            }
        }
    }
    cout << "Inverted filter applied successfully." << endl;
}

// Black & White filter
void black_white_filter(Image& image) {
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            unsigned int avg = 0;

            for (int c = 0; c < 3; ++c) {
                avg += image(x, y, c);
            }

            avg /= 3;

            unsigned char bw = (avg < 127 ? 0 : 255);

            for (int c = 0; c < 3; ++c) {
                image(x, y, c) = bw;
            }
        }
    }
    cout << "Black & White filter applied successfully." << endl;
}
// Flip image horizontally
void flip_horizontal(Image& image) {
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width / 2; ++x) {
            for (int c = 0; c < 3; ++c) {

                int temp = image(x, y, c);
                image(x, y, c) = image(image.width - 1 - x, y, c);
                image(image.width - 1 - x, y, c) = temp;
            }
        }
    }
    cout << "Horizontal flip applied successfully." << endl;
}
// Flip image vertically
void flip_vertical(Image& image) {
    for (int y = 0; y < image.height / 2; ++y) {
        for (int x = 0; x < image.width; ++x) {
            for (int c = 0; c < 3; ++c) {

                int temp = image(x, y, c);
                image(x, y, c) = image(x, image.height - 1 - y, c);
                image(x, image.height - 1 - y, c) = temp;
            }
        }
    }
    cout << "Vertical flip applied successfully." << endl;
}
void rotate90(Image& image) {
    Image rotated(image.height, image.width);
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            for (int c = 0; c < 3; ++c) {
                rotated(y, image.width - 1 - x, c) = image(x, y, c);
            }
        }
    }

    image = rotated;
    cout << "Image rotated 90 degrees clockwise successfully." << endl;
}
void rotate180(Image& image) {
    Image rotated(image.width, image.height);

    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            for (int c = 0; c < 3; ++c) {
                rotated(image.width - 1 - x, image.height - 1 - y, c) = image(x, y, c);
            }
        }
    }

    image = rotated;
    cout << "Image rotated 180 degrees successfully." << endl;
}
void rotate270(Image& image) {
    Image rotated(image.height, image.width);

    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            for (int c = 0; c < 3; ++c) {
                rotated(image.height - 1 - y, x, c) = image(x, y, c);
            }
        }
    }

    image = rotated;
    cout << "Image rotated 270 degrees clockwise successfully." << endl;
}
void merge_filter(Image& image) {
    string f1, f2;
    cout << "Pls enter first image filename: ";
    cin >> f1;
    cout << "Pls enter second image filename: ";
    cin >> f2;

    Image img1,img2 ;
    if (!img1.loadNewImage(f1) || !img2.loadNewImage(f2)) {
        cerr << "Error: Failed to load one of the images.\n";
        return;
    }

    Image result(img1.width, img1.height);

    for (int i = 0; i < img1.width; i++) {
        for (int j = 0; j < img1.height; j++) {
            int srcX = i * img2.width / img1.width;
            int srcY = j * img2.height / img1.height;
            for (int k = 0; k < 3; k++) {
                result(i, j, k) = (img1(i, j, k) + img2(srcX, srcY, k)) / 2;
            }
        }

    }
    image = result;
    cout << "Merge filter applied successfully." << endl;
}
// Crop Images filter
Image crop_image(const Image& image, int x, int y, int W, int H) {
    if (x < 0 || y < 0 || x + W > image.width || y + H > image.height) {
        cerr << "Error: Crop dimensions exceed image boundaries." << endl;
        return image;
    }

    Image cropped(W, H);

    for (int j = 0; j < H; ++j) {
        for (int i = 0; i < W; ++i) {
            for (int c = 0; c < 3; ++c) {
                cropped(i, j, c) = image(x + i, y + j, c);
            }
        }
    }
    cout << "Crop applied successfully." << endl;
    return cropped;
}
void edge_detection_filter(Image& image) {
    Image result(image.width, image.height);

    for (int y = 1; y < image.height - 1; ++y) {
        for (int x = 1; x < image.width - 1; ++x) {
            int gx = 0, gy = 0;

            for (int c = 0; c < 3; ++c) {
                gx = abs(image(x + 1, y, c) - image(x - 1, y, c));
                gy = abs(image(x, y + 1, c) - image(x, y - 1, c));
            }

            int edge = (gx + gy) / 2;
            unsigned char color = (edge > 35 ? 0 : 255);

            for (int c = 0; c < 3; ++c)
                result(x, y, c) = color;
        }
    }

    image = result;
    cout << "Simple edge filter applied successfully."<<endl;
}
// frame filter
void frame_image(Image& image , int color) {
    unsigned char r = 0, g = 0, b = 0;

    if (color == 1) r = g = b = 255;      // White
    else if (color == 2) r = 255;         // Red
    else if (color == 3) g = 255;         // Green
    else if (color == 4) b = 255;         // Blue
    else if (color == 5) r = g = b = 0;   // Black
    Image frameImage (image.width+10, image.height+10);
     // put the image  pixels in bigger image to make space for frame
     for (int y = 0; y < image.height; ++y) {
         for (int x = 0; x < image.width; ++x) {
             for (int c = 0; c < 3; ++c) {
                 frameImage(x+5, y+5, c) = image(x, y, c);
             }
         }
     }
     for (int y = 0; y < frameImage.height; ++y) {
         for (int x = 0; x < frameImage.width; ++x) {
             bool isFrame = (x < 5) || (x >= frameImage.width - 5) ||
                            (y < 5) || (y >= frameImage.height - 5);
             if (isFrame) {
                 frameImage(x, y, 0) = r;
                 frameImage(x, y, 1) = g;
                 frameImage(x, y, 2) = b;
             }
         }
     }
    image = frameImage;
    cout << "Frame image applied successfully." << endl;
}
// resize image filter
void resizeFilter(Image& image , float newWidth, float newHeight) {
    Image newImage(newWidth, newHeight);
    int scaleX , scaleY ;
    for (int y = 0; y < newImage.height; ++y) {
        for (int x = 0; x < newImage.width; ++x) {
            int pixlX = (float)x * image.width / newWidth;
            int pixlY = (float)y * image.height / newHeight;
            scaleX = round(pixlX);
            scaleY = round(pixlY);
            scaleX = min(scaleX, image.width-1);
            scaleY = min(scaleY, image.height-1);
            for (int c = 0; c < 3; ++c) {
                newImage(x, y, c) = image(scaleX, scaleY, c);
            }
        }
    }
    image = newImage;
    cout << "Resize filter applied successfully." << endl;
}
// darken and lighten image
void darken_lighten_Filter(Image& image , int m) {
    float factor = (m == 1) ? 1.5 : 0.5;
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    int x;
                    x = image(i, j, k)*factor;
                    if (x>255) {
                        x = 255;
                    }
                    image(i, j, k) = x;
                }
            }
        }
    cout << ((m == 1) ? "Lighten" : "Darken") << " Filter applied successfully." << endl;
}
// 2- gaussian filter (blur)
void SeparableGaussianBlur(Image& image, int kernelSize, double sigma) {

    int radius = kernelSize / 2;

    // Build 1D Gaussian kernel
    vector<double> kernel(kernelSize);
    double sum = 0.0;
    double denom = 2.0 * sigma * sigma;

    for (int i = -radius; i <= radius; ++i) {
        double value = exp(-(i * i) / denom);
        kernel[i + radius] = value;
        sum += value;
    }
    for (int i = 0; i < kernelSize; ++i)
        kernel[i] /= sum;

    Image temp(image.width, image.height);

    // Horizontal pass
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            double sumR = 0.0, sumG = 0.0, sumB = 0.0;

            for (int k = -radius; k <= radius; ++k) {
                int sx = std::clamp(x + k, 0, image.width - 1);

                unsigned char r = image.getPixel(sx, y, 0);
                unsigned char g = image.getPixel(sx, y, 1);
                unsigned char b = image.getPixel(sx, y, 2);

                double kv = kernel[k + radius];
                sumR += r * kv;
                sumG += g * kv;
                sumB += b * kv;
            }

            temp.setPixel(x, y, 0, (unsigned char)(clamp(sumR, 0.0, 255.0)));
            temp.setPixel(x, y, 1, (unsigned char)(clamp(sumG, 0.0, 255.0)));
            temp.setPixel(x, y, 2, (unsigned char)(clamp(sumB, 0.0, 255.0)));
        }
    }

    Image out(image.width, image.height);

    // Vertical pass
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            double sumR = 0.0, sumG = 0.0, sumB = 0.0;

            for (int k = -radius; k <= radius; ++k) {
                int sy = clamp(y + k, 0, image.height - 1);

                unsigned char r = temp.getPixel(x, sy, 0);
                unsigned char g = temp.getPixel(x, sy, 1);
                unsigned char b = temp.getPixel(x, sy, 2);

                double kv = kernel[k + radius];
                sumR += r * kv;
                sumG += g * kv;
                sumB += b * kv;
            }

            out.setPixel(x, y, 0, (unsigned char)(clamp(sumR, 0.0, 255.0)));
            out.setPixel(x, y, 1, (unsigned char)(clamp(sumG, 0.0, 255.0)));
            out.setPixel(x, y, 2, (unsigned char)(clamp(sumB, 0.0, 255.0)));
        }
    }
    image = out;
    cout << "Separable Gaussian Blur applied successfully." << endl;
}
void warm_image(Image& image) {
        for (int y = 0; y < image.height; ++y) {
            for (int x = 0; x < image.width; ++x) {
                int r = image(x, y, 0);
                int g = image(x, y, 1);
                int b = image(x, y, 2);


                r = min(int(r * 1.1 + 20), 255);
                g = min(int(g * 1.05 + 10), 255);
                b = min(int(b * 0.9), 255);

                image(x, y, 0) = r;
                image(x, y, 1) = g;
                image(x, y, 2) = b;
            }
        }
        cout << "warm filter applied successfully." << endl;
    }
void infrared_filter(Image& image) {
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            int r = image(x, y, 0);
            int g = image(x, y, 1);
            int b = image(x, y, 2);

            // Boost red, reduce others
            r = min(255, int(r * 1.5));
            g = int(g * 0.5);
            b = int(b * 0.2);

            image(x, y, 0) = r;
            image(x, y, 1) = g;
            image(x, y, 2) = b;
        }
    }
    cout << "Infrared filter applied successfully."<<endl;
}
void purple_filter(Image& image) {
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {

            unsigned char r = image(x, y, 0);
            unsigned char g = image(x, y, 1);
            unsigned char b = image(x, y, 2);

            int new_r = (int)r + 40;
            int new_g = (int)g - 30;
            int new_b = (int)b + 60;


            r = (unsigned char)std::min(255, std::max(0, new_r));
            g = (unsigned char)std::min(255, std::max(0, new_g));
            b = (unsigned char)std::min(255, std::max(0, new_b));


            image(x, y, 0) = r;
            image(x, y, 1) = g;
            image(x, y, 2) = b;
        }
    }
    cout << "Purple filter applied successfully."<<endl;
}
// Helper function to save an image
bool save_image(Image& image) {
    string outputFilename;
    cout << "\nEnter the filename to save the new image" << endl;
    cout << "(specify extension .jpg, .bmp, .png, or .tga): ";
    cin.ignore(); // تجاهل الـ newline
    getline(cin, outputFilename);

    if (!image.saveImage(outputFilename)) {
        cerr << "Error: Failed to save image as '" << outputFilename << "'" << endl;
        return false;
    }

    cout << "Image saved successfully as '" << outputFilename << "'!" << endl;
    return true;
}

int main() {
    bool x = 1;
    while (x) {
        string inputFilename;
        cout << "Please enter the image name to load (e.g., photo.jpg):" << endl;
        getline(cin, inputFilename);

        Image myImage;

        if (!myImage.loadNewImage(inputFilename)) {
            cerr << "Error: Could not load image '" << inputFilename << "'" << endl;
            return 1;
        }

        cout << "Image '" << inputFilename << "' loaded successfully!" << endl;

        cout << "\nSelect the filter you want to apply:" << endl;
        cout << "1: Grayscale Filter" << endl;
        cout << "2: Black and White Filter" << endl;
        cout << "3: Inverted Filter" << endl;
        cout << "4: Merge Filter\n";
        cout << "5: Flip Image Filter\n";
        cout << "6: Rotate Image Filter\n";
        cout << "7: Darken and Lighten Filter\n";
        cout << "8: Crop Image Filter\n";
        cout << "9: Frame Image Filter\n";
        cout << "10: Detect Image Edges Filter\n";
        cout << "11: Resize Image Filter\n";
        cout << "12: Blur Image Filter\n";
        cout << "13: Warm Image Filter\n";
        cout << "14: Infrared Image Filter\n";
        cout << "15: Purple Image Filter\n";
        cout << "Enter Filter Number: ";


        int filter;
        cin >> filter;

        switch (filter) {
        case 1: {
            grey_filter(myImage);
            break;
        }
        case 2: {
            black_white_filter(myImage);
            break;
        }
        case 3: {
            inverted_filter(myImage);
            break;
        }
        case 4: {
           merge_filter(myImage) ;
            break;
        }
        case 5: {
            int p;
            cout << "Please select\n " << "1. Vertical flip\n" << "2. Horizontal flip\n";
            cin >> p;
            if (p == 1) {
                flip_vertical(myImage);
                break;

            }
            else if (p == 2) {
                flip_horizontal(myImage);
                break;

            }
        break;
        }
        case 6: {
            int z;
            cout << "Select the degree of rotation \n" << "1. 90 Degree\n" << "2. 180 Degree\n" << "3. 270 Degree\n";
            cin >> z;
            if (z == 1) {
                rotate90(myImage);
                break;
            }
            else if (z == 2) {
                rotate180(myImage);
                break;
            }
            else if (z == 3) {
                rotate270(myImage);
                break;
            }
            break;
        }
            case 7: {
            cout << "if you want to light image enter 1 or to dark it enter 2 : " << endl;
            int m;
            cin >> m;
            darken_lighten_Filter(myImage, m);
            break;

        }
            case 8: {
            int X, Y, W, H;
            cout << "Image dimensions: Width = " << myImage.width ;
            cout << ", Height = " << myImage.height << endl;
            cout << "Enter the top-left corner (x y): ";
            cin >> X >> Y;
            cout << "Enter width and height of the crop area: ";
            cin >> W >> H;

            myImage = crop_image(myImage, X, Y, W, H);
            break;

        }
            case 9: {
            int color;
            cout << "1: White " << "\n2: Red " << "\n3: Green " << "\n4: Blue " << "\n5: Black \n";
            cout << "Enter The Number of The Color for Frame : \n";
            cin >> color;
            frame_image(myImage , color);
            break;

        }
            case 10: {
            edge_detection_filter(myImage);
            break;

        }
            case 11: {
            float newWidth, newHeight;
            float ratio;
            cout << "Enter resize ratio (0 if you want to enter width and height manually): ";
            cin >> ratio;

            if (ratio == 0) {
                cout << "Enter new width: ";
                cin >> newWidth;
                cout << "Enter new height: ";
                cin >> newHeight;
            } else {
                newWidth = myImage.width * ratio;
                newHeight = myImage.height * ratio;
            }
            resizeFilter(myImage, newWidth, newHeight);
            break;

        }
            case 12: {
            SeparableGaussianBlur(myImage ,21 , 10.0 );
            break;
        }
                case 13: {
                warm_image(myImage);
                break;
            }
                case 14: {
                infrared_filter(myImage);
                break;
            }
                case 15: {
                purple_filter(myImage);
                break;
            }
        default:
            cout << "Invalid filter number entered." << endl;
            return 1;

        }
        if (!save_image(myImage)) return 1;

        string response;
        cout << "If you want to continue type yes \n";
        cin >> response;
        cin.ignore();
        transform(response.begin(), response.end(), response.begin(), ::tolower); // include "algorithm"
        if (response != "yes") {
            x = 0;
        }
    }
    return 0;
}