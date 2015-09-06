#include "Core/Film.h"
#include "Utility/func.h"

#include <cstdio>
#include <cmath>

void Film::start(){
    int wt, ht, l, p, i, j;
    w = xmax - xmin;
    h = ymax - ymin;
    image = CImg<double>(w, h, 1, 3);
    dispImage = CImg<double>(w, h, 1, 3);
    image.fill(0);
    dispImage.fill(0);
    //sampler = new Sampler;
    //sampler->generateSample(sampleRate);
    wt = w;
    ht = h;
    l = 1;
    while ((wt > 0) || (ht > 0)){
        l *= 2;
        wt /= 2;
        ht /= 2;
    }
    sampleList.emplace_back(0, 0, l);
    while (l > 0){
        for (i = 0; i <= (w - 1) / l; i++)
            for (j = 0; j <= (h - 1) / l; j++)
                if (((i % 2) != 0) || ((j % 2) != 0))
                    sampleList.emplace_back(i * l, j * l, l);
        l /= 2;
    }
    if (directDisplay == true){
        disp = CImgDisplay(dispImage, "rendering image", 0);
        disp.show();
    }
}

void Film::getSample(int k, double &x, double &y){
    currentIndex = k;
    if (k < w * h)
        std::tie(cx, cy, std::ignore) = sampleList[k];
    else{
        cx = (k / h) % w;
        cy = k % h;
    }
    x = (xmin + cx + randReal()) / scale;
    y = (ymax - cy - randReal()) / scale;
    //sampler->getSample(k, tx, ty);
}

void Film::setResult(const RGBColor &color){
    int l;
    /*
    image(cx, cy, 0, 0) += (!(color.r >= 0)) ? 0 : ((color.r <= 3) ? color.r : 3);
    image(cx, cy, 0, 1) += (!(color.g >= 0)) ? 0 : ((color.g <= 3) ? color.g : 3);
    image(cx, cy, 0, 2) += (!(color.b >= 0)) ? 0 : ((color.b <= 3) ? color.b : 3);
    */
    image(cx, cy, 0, 0) += (!(color.r >= 0)) ? 0 : color.r;
    image(cx, cy, 0, 1) += (!(color.g >= 0)) ? 0 : color.g;
    image(cx, cy, 0, 2) += (!(color.b >= 0)) ? 0 : color.b;
    if (directDisplay == true){
        dcolor[0] = pow(image(cx, cy, 0, 0) / (1 + currentIndex / (w * h)), 1.0 / 2.2) * 255;
        dcolor[1] = pow(image(cx, cy, 0, 1) / (1 + currentIndex / (w * h)), 1.0 / 2.2) * 255;
        dcolor[2] = pow(image(cx, cy, 0, 2) / (1 + currentIndex / (w * h)), 1.0 / 2.2) * 255;
        dcolor[0] = dcolor[0] < 0 ? 0 : dcolor[0] > 255 ? 255 : dcolor[0];
        dcolor[1] = dcolor[1] < 0 ? 0 : dcolor[1] > 255 ? 255 : dcolor[1];
        dcolor[2] = dcolor[2] < 0 ? 0 : dcolor[2] > 255 ? 255 : dcolor[2];
        if (currentIndex < w * h){
            l = std::get<2>(sampleList[currentIndex]);
            dispImage.draw_rectangle(cx, cy, cx + l - 1, cy + l - 1, dcolor);
        }
        else
            dispImage.draw_rectangle(cx, cy, cx, cy, dcolor);
        if (currentIndex % 100 == 0)
            disp.display(dispImage);
    }
}

void Film::finish(){
    image /= (sampleRate * sampleRate);
    if (directDisplay)
        while (!disp.is_closed())
            disp.wait();
    //delete sampler;
}

void Film::saveImage(char *filename, bool isHDR){
    int i, j, k;
    if (!isHDR){
        for (i = 0; i < xmax - xmin; i++)
            for (j = 0; j < ymax - ymin; j++)
                for (k = 0; k < 3; k++)
                    image(i, j, 0, k) = pow(image(i, j, 0, k), 1.0 / 2.2);
        image *= 255;
        image.max(0.0);
        image.min(255);
        image.save(filename);
    }
    else{
        image.max(0.0);
        image.save_exr(filename);
    }
}
