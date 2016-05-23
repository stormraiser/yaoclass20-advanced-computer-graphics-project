#include "inc.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>

/*
void billardBall(){
    Scene *scene = new Scene;
    Camera *camera = new PerspectiveCamera;
    Film *film = new Film(250, -200, 200, -150, 100);
    camera->setPosition(20, 0, 6, 0, 0, 0, 0, 0, 1);

    Cuboid *cuboid1 = new Cuboid(0, 0, -4, 100, 100, 1.99);
    Sphere *sphere2 = new Sphere(0, 0, 0, 3);
        sphere2->rotate(-30, 0, 0, 1);
        sphere2->rotate(30, 1, 0, 0);
        sphere2->translate(-5, 6, 0);
    Sphere *sphere3 = new Sphere(0, 0, 0, 3);
        sphere3->rotate(30, 0, 0, 1);
        sphere3->rotate(-30, 1, 0, 0);
        sphere3->translate(-5, -6, 0);
    Sphere *sphere4 = new Sphere(0, 0, 0, 3);
        sphere4->rotate(-30, 0, 1, 0);
        sphere4->translate(5, 0, 0);
    Cuboid *cuboid5 = new Cuboid(0, 0, 50, 150, 150, 1);

    BitmapTexture *texture2 = new BitmapTexture("ball10.png");
    BitmapTexture *texture3 = new BitmapTexture("ball13.png");
    BitmapTexture *texture4 = new BitmapTexture("ball8.png");
    GlossySpecular *bsdf1 = new GlossySpecular(0.4, 5);
    PerfectSpecular *bsdf3a = new PerfectSpecular(1);
    GlossySpecular *bsdf3b = new GlossySpecular(0.9, 1);
    Emissive *bsdf5 = new Emissive(1);
    BaseSurface *surface1 = new BaseSurface(bsdf1, RGBColor(0.1, 1, 0.1));
    BaseSurface *surface3a = new BaseSurface(bsdf3a, 1);
    BaseSurface *surface2b = new BaseSurface(bsdf3b, texture2);
    BaseSurface *surface3b = new BaseSurface(bsdf3b, texture3);
    BaseSurface *surface4b = new BaseSurface(bsdf3b, texture4);
    FresnelBlendedSurface *surface2 = new FresnelBlendedSurface(surface3a, surface2b, 1.4);
    FresnelBlendedSurface *surface3 = new FresnelBlendedSurface(surface3a, surface3b, 1.4);
    FresnelBlendedSurface *surface4 = new FresnelBlendedSurface(surface3a, surface4b, 1.4);
    BaseSurface *surface5 = new BaseSurface(bsdf5, 1);
    Material *material1 = new Material(surface1);
    Material *material2 = new Material(surface2);
    Material *material3 = new Material(surface3);
    Material *material4 = new Material(surface4);
    Material *material5 = new Material(surface5);

    cuboid1->material = material1;
    sphere2->material = material2;
    sphere3->material = material3;
    sphere4->material = material4;
    cuboid5->material = material5;

    scene->addObject(cuboid1);
    scene->addObject(sphere2);
    scene->addObject(sphere3);
    scene->addObject(sphere4);
    scene->addObject(cuboid5);

    PureColor *background = new PureColor(0);
    scene->setBackground(background);

    MonteCarloPathTracer *renderer = new MonteCarloPathTracer(scene, camera, film, 2);
    renderer->setMaximumDepth(20);
    renderer->render();

    film->saveImage("output.png");
}

void milk(){
    Scene *scene = new Scene;
    Camera *camera = new PerspectiveCamera;
    Film *film = new Film(2400, -400, 400, -400, 400);
    camera->setPosition(40, 30, 15, 0, 0, 5, 0, 0, 1);

    Cuboid *floor1 = new Cuboid(0, 0, -1, 100, 100, 2);
    Cuboid *wall2 = new Cuboid(0, -51, 50, 100, 2, 100);
    Cuboid *wall3 = new Cuboid(0, 51, 50, 100, 2, 100);
    Cuboid *wall4 = new Cuboid(-51, 0, 50, 2, 100, 100);
    Cuboid *wall5 = new Cuboid(51, 0, 50, 2, 100, 100);
    Cuboid *ceil6 = new Cuboid(0, 0, 101, 100, 100, 2);
    //Cuboid *light7 = new Cuboid(0, 49, 50, 80, 2, 80);
    Cuboid *light7 = new Cuboid(0, 0, 39, 90, 90, 2);
    PrimitivePtr glass8a = new Cylinder(0, 0, 5, 2, 9.9);
    PrimitivePtr glass8b = new Cylinder(0, 0, 6, 1.8, 11.6);
    Cylinder *milk9 = new Cylinder(0, 0, 3, 1.81, 5.62, -1);

    BitmapTexture *texture1 = new BitmapTexture("woodsq.png");
    //CheckerColor *texture1 = new CheckerColor(RGBColor(1, 0.125, 0.125), RGBColor(1, 0.422, 0.422), 50, 50, 0, 0);
    GlossySpecular *bsdf1a = new GlossySpecular(0.8, 1);
    PerfectSpecular *bsdf1b = new PerfectSpecular(0.3);
    Emissive *bsdf7 = new Emissive(1);
    Fresnel *bsdf8 = new Fresnel(1);
    Fresnel *bsdf9a = new Fresnel(1);
    PhaseIsotropic *bsdf9b = new PhaseIsotropic(1);

    BaseSurface *surface1a = new BaseSurface(bsdf1a, texture1);
    BaseSurface *surface1b = new BaseSurface(bsdf1b, 1);
    FresnelBlendedSurface *surface1 = new FresnelBlendedSurface(surface1a, surface1b, 1.3);
    BaseSurface *surface2 = new BaseSurface(bsdf1a, 1);
    BaseSurface *surface7 = new BaseSurface(bsdf7, RGBColor(1, 0.945, 0.808));
    BaseSurface *surface8 = new BaseSurface(bsdf8, 1);
    BaseSurface *surface9 = new BaseSurface(bsdf9a, 1);

    Material *material1 = new Material(surface1);
    Material *material2 = new Material(surface2);
    Material *material7 = new Material(surface7);
    Material *material8 = new Material(surface8, 1.46, RGBColor(0.7, 0.7, 0.8));
    Material *material9 = new Material(surface9, 1.333, 1, bsdf9b, 0.05, 0.8);

    floor1->material = material1;
    wall2->material = material2;
    wall3->material = material2;
    wall4->material = material2;
    wall5->material = material2;
    ceil6->material = material2;
    light7->material = material7;
    glass8a->material = material8;
    glass8b->material = material8;
    milk9->material = material9;

    CSGObject *glass8 = glass8a - glass8b;
    glass8->setChildCSG();

    scene->addObject(floor1);
    scene->addObject(wall2);
    scene->addObject(wall3);
    scene->addObject(wall4);
    scene->addObject(wall5);
    scene->addObject(ceil6);
    scene->addObject(light7);
    scene->addObject(glass8);
    scene->addObject(milk9);

    MonteCarloPathTracer *renderer = new MonteCarloPathTracer(scene, camera, film, 2);
    renderer->setMaximumDepth(100);
    renderer->render();

    film->saveImage("output.png");
}

void hdrSky(){
    Scene *scene = new Scene;
    Camera *camera = new PerspectiveCamera;
    Film *film = new Film(1500, -640, 640, -360, 360);
    camera->setPosition(35, 75, 20, 0, 0, 7.5, 0, 0, 1);

    PrimitivePtr base1a = new Cuboid(0, 0, -5, 100000, 100000, 10);
    PrimitivePtr base1b = new Cuboid(0, 0, 5, 960, 960, 10.1);
    Sphere *sphere2 = new Sphere(10, -20, 7.5, 7.5);
    Sphere *sphere3 = new Sphere(-10, 0, 7.5, 7.5);
    Sphere *sphere4 = new Sphere(10, 20, 7.5, 7.5);

    GlossySpecular *bsdf1 = new GlossySpecular(1, 1);
    PerfectSpecular *bsdf2 = new PerfectSpecular(1);
    Fresnel *bsdf4 = new Fresnel(1);

    BaseSurface *surface1 = new BaseSurface(bsdf1, 1);
    BaseSurface *surface2 = new BaseSurface(bsdf2, 1);
    BaseSurface *surface4 = new BaseSurface(bsdf4, 1);

    Material *material1 = new Material(surface1);
    Material *material2 = new Material(surface2);
    Material *material4 = new Material(surface4, 1.46);

    base1a->material = material1;
    base1b->material = material1;
    sphere2->material = material2;
    sphere3->material = material2;
    sphere4->material = material2;

    CSGObject *base1 = base1a - base1b;

    scene->addObject(base1);
    scene->addObject(sphere2);
    scene->addObject(sphere3);
    scene->addObject(sphere4);

    BitmapTexture *background = new BitmapTexture("sky.exr", true, 0.01);
    scene->setBackground(background);

    MonteCarloPathTracer *renderer = new MonteCarloPathTracer(scene, camera, film, 2);
    renderer->setMaximumDepth(20);
    renderer->render();

    film->saveImage("output.exr", true);
}
*/

void photonMappingTest(){
    Scene *scene = new Scene;
    Camera *camera = new PerspectiveCamera;
    Film *film = new Film(150, -200, 200, -200, 200);
    //Film *film = new Film(150, -50, 50, -50, 50);
    camera->setPosition(10, 10, 3, 0, 0, 0, 0, 0, 1);

    Cuboid *cuboid1 = new Cuboid(0, -11, 0, 20, 2, 20);
    Cuboid *cuboid2 = new Cuboid(-11, 0, 0, 2, 20, 20);
    Sphere *sphere3 = new Sphere(-5, 0, 0, 1.5);
    Sphere *sphere4 = new Sphere(0, -5, 0, 1.5);

    LambertianBSDF *bsdf1 = new LambertianBSDF(RGBColor(1, 0.2, 0.2));
    LambertianBSDF *bsdf2 = new LambertianBSDF(RGBColor(0.2, 0.2, 1));
    FresnelBSDF *bsdf3 = new FresnelBSDF();
    SpecularBSDF *bsdf4 = new SpecularBSDF(1);

    Material *material1 = new Material(bsdf1);
    Material *material2 = new Material(bsdf2);
    Material *material3 = new Material(bsdf3, 1.5);
    Material *material4 = new Material(bsdf4);

    PointLight *light1 = new PointLight(0, 0, 0, 1, 300);

    cuboid1->material = material1;
    cuboid2->material = material2;
    sphere3->material = material3;
    sphere4->material = material3;

    scene->addObject(cuboid1);
    scene->addObject(cuboid2);
    scene->addObject(sphere3);
    scene->addObject(sphere4);
    scene->addLight(light1);

    PhotonMappingRenderer *renderer = new PhotonMappingRenderer(scene, camera, film, 4);
    //renderer->setPhotonNumber(50000, 20000, 1, 100);
    renderer->setPhotonNumber(100000, 100000, 100, 100);
    renderer->setQuality(10, 10);
    renderer->setRenderMode(PhotonMappingRenderer::DirectComponent | PhotonMappingRenderer::SpecularComponent | PhotonMappingRenderer::CausticComponent);
    //renderer->setRenderMode(PhotonMappingRenderer::IndirectComponent);
    //renderer->setRenderMode(PhotonMappingRenderer::NoGather | PhotonMappingRenderer::SpecularComponent);
    //renderer->setRenderMode(PhotonMappingRenderer::PhotonVisualize);
    renderer->setMaximumDepth(10);
    renderer->buildPhotonMap();
    renderer->render();

    film->saveImage("output.png");
}

void kCaustic(){
    Scene *scene = new Scene;
    Camera *camera = new PerspectiveCamera;
    Film *film = new Film(300, -200, 200, -200, 200);
    camera->setPosition(5, 20, 25, 0, 0, 0, 0, 0, 1);

    Cuboid *floor1 = new Cuboid(0, 0, -1, 100, 100, 2);
    PrimitivePtr k2a = new Cylinder(0, 0, 5, 8, 10);
    PrimitivePtr k2b = new Cylinder(0, 0, 5, 7.8, 11);
    PrimitivePtr k2c = new Cuboid(0, 5, 5, 12, 10, 11);

    BitmapTexture *texture1 = new BitmapTexture("woodsq.png");

    LambertianBSDF *bsdf1 = new LambertianBSDF(1, texture1);
    SpecularBSDF *bsdf2 = new SpecularBSDF(RGBColor(1, 0.8, 0.5));

    Material *material1 = new Material(bsdf1);
    Material *material2 = new Material(bsdf2);

    floor1->material = material1;
    k2a->material = material2;
    k2b->material = material2;
    k2c->material = material2;

    CSGObject *k2 = k2a - k2b - k2c;

    PointLight *light1 = new PointLight(0, 30, 30, 1, 1000);

    scene->addObject(floor1);
    scene->addObject(k2);
    scene->addLight(light1);

    PhotonMappingRenderer *renderer = new PhotonMappingRenderer(scene, camera, film, 1);
    renderer->setPhotonNumber(10000, 10000, 10, 10);
    renderer->setQuality(10, 10);
    renderer->setRenderMode(PhotonMappingRenderer::DirectComponent | PhotonMappingRenderer::SpecularComponent | PhotonMappingRenderer::CausticComponent);

    renderer->setMaximumDepth(10);
    renderer->buildPhotonMap();
    renderer->render();

    film->saveImage("output.png");
}

void cylinderCaustic(int argc, char **argv){
    int i;
    char filename[100];

    Scene *scene = new Scene;
    Camera *camera = new PerspectiveCamera;
    //Film *film = new Film(450, -300, 300, -300, 300);
    Film *film = new Film(300, -200, 200, -200, 200);
    camera->setPosition(15, -15, 15, 0, -3, 0, 0, 0, 1);

    Cuboid *floor1 = new Cuboid(0, 0, -1, 100, 100, 2);
    PrimitivePtr cup2a = new Cylinder(0, 0, 6, 5, 12);
    PrimitivePtr cup2b = new Cylinder(0, 0, 6.2, 4.8, 12);
    Cylinder *liquid3 = new Cylinder(0, 0, 4.1, 4.9, 8, -1);

    BitmapTexture *texture1 = new BitmapTexture("woodsq.png");

    LambertianBSDF *bsdf1 = new LambertianBSDF(1, texture1);
    FresnelBSDF *bsdf2 = new FresnelBSDF();

    Material *material1 = new Material(bsdf1);
    Material *material2 = new Material(bsdf2, 1.52);
    Material *material3 = new Material(bsdf2, 1.333, RGBColor(0.9, 0.6, 0.3));

    floor1->material = material1;
    cup2a->material = material2;
    cup2b->material = material2;
    liquid3->material = material3;

    PointLight *light1 = new PointLight(0, 30, 30, 1, 3000);

    CSGObject *cup2 = cup2a - cup2b;
    cup2->setChildCSG();

    scene->addObject(floor1);
    scene->addObject(cup2);
    scene->addObject(liquid3);
    scene->addLight(light1);

    PhotonMappingRenderer *renderer = new PhotonMappingRenderer(scene, camera, film, 1);
    renderer->setPhotonNumber(10000, 10000, 10, 10);
    renderer->setQuality(10, 10);
    renderer->setRenderMode(PhotonMappingRenderer::DirectComponent |
                            PhotonMappingRenderer::SpecularComponent |
                            PhotonMappingRenderer::CausticComponent |
                            PhotonMappingRenderer::AllowMultiray);
    //renderer->setRenderMode(PhotonMappingRenderer::NoGather | PhotonMappingRenderer::SpecularComponent);

    renderer->setMaximumDepth(10);
    renderer->setMaximumMultirayDepth(1);
    if (argc == 2)
        renderer->loadPhotonMap(argv[1]);
    else{
        renderer->buildPhotonMap();
        renderer->savePhotonMap("photonMap.txt");
    }

    /*
    for (i = 0; true; i++){
        printf("%d\n", i);
        renderer->render();
        sprintf(filename, "output%d.png", i);
        film->saveImage(filename);
    }
    */
    renderer->render();
    film->saveImage("output.png");
    //film->saveImage("output.exr", true);
}

void indirectTest(int argc, char **argv){
    Scene *scene = new Scene;
    Camera *camera = new PerspectiveCamera;
    Film *film = new Film(250, -250, 250, -250, 250);
    //Film *film = new Film(250, -70, -50, -55, -35);
    camera->setPosition(0, 17, 0, 0, 0, 0, 0, 0, 1);

    Cuboid *cuboid1 = new Cuboid(0, 0, -11, 20, 20, 2);
    Cuboid *cuboid2 = new Cuboid(11, 0, 0, 2, 20, 20);
    Cuboid *cuboid3 = new Cuboid(0, 0, 11, 20, 20, 2);
    Cuboid *cuboid4 = new Cuboid(-11, 0, 0, 2, 20, 20);
    Cuboid *cuboid5 = new Cuboid(0, -11, 0, 20, 2, 20);
    Sphere *sphere6 = new Sphere(6, -6, -6, 4);
    Sphere *sphere7 = new Sphere(-6, -1, -5, 4);
    MeshObject *knot8 = new MeshObject("knot.obj");
    ///*
    knot8->scale(0.5);
    knot8->translate(0, 0, -6.5);
    //*/
    /*
    knot8->loadOBJ("bunny_0.1.obj");
    knot8->scale(60);
    knot8->rotate(90, 1, 0, 0);
    knot8->rotate(180, 0, 0, 1);
    knot8->translate(-3, 0, -10);
    */

    PerlinNoise3D *texture8 = new PerlinNoise3D(8, 0.5, 12345, "marble01.jpg", 10, 10, 10, 3);

    LambertianBSDF *bsdf1 = new LambertianBSDF(RGBColor(0.8, 0.1, 0.1));
    LambertianBSDF *bsdf2 = new LambertianBSDF(RGBColor(0.8, 0.8, 0.1));
    LambertianBSDF *bsdf3 = new LambertianBSDF(RGBColor(0.1, 0.8, 0.1));
    LambertianBSDF *bsdf4 = new LambertianBSDF(RGBColor(0.1, 0.1, 0.8));
    LambertianBSDF *bsdf5 = new LambertianBSDF(RGBColor(0.8, 0.8, 0.8));
    SpecularBSDF *bsdf6 = new SpecularBSDF;
    FresnelBSDF *bsdf7 = new FresnelBSDF;
    PhaseIsotropic *bsdf8 = new PhaseIsotropic(1, texture8);

    Material *material1 = new Material(bsdf1);
    Material *material2 = new Material(bsdf2);
    Material *material3 = new Material(bsdf3);
    Material *material4 = new Material(bsdf4);
    Material *material5 = new Material(bsdf5);
    Material *material6 = new Material(bsdf6);
    Material *material7 = new Material(bsdf7, 1.4);
    Material *material8 = new Material(bsdf7, 1.4, 1, bsdf8, 0.005);

    cuboid1->material = material1;
    cuboid2->material = material2;
    cuboid3->material = material3;
    cuboid4->material = material4;
    cuboid5->material = material5;
    sphere6->material = material6;
    sphere7->material = material7;
    knot8->material = material8;

    //PointLight *light1 = new PointLight(0, 0, 0, 1, 1000);
    SquareLight *light1 = new SquareLight(0, 0, 9.999, 0, 0, -1, 0, 1, 0, 4, 4, 1, 4000);

    scene->addObject(cuboid1);
    scene->addObject(cuboid2);
    scene->addObject(cuboid3);
    scene->addObject(cuboid4);
    scene->addObject(cuboid5);
    //scene->addObject(sphere6);
    //scene->addObject(sphere7);
    scene->addObject(knot8);
    scene->addLight(light1);

    PhotonMappingRenderer *renderer = new PhotonMappingRenderer(scene, camera, film, 4);
    renderer->setPhotonNumber(1000000, 0, 100, 100);
    renderer->setQuality(1, 16);
    renderer->setRenderMode(0
                            | PhotonMappingRenderer::DirectComponent
                            | PhotonMappingRenderer::IndirectComponent
                            | PhotonMappingRenderer::SpecularComponent
                            | PhotonMappingRenderer::CausticComponent
                            //| PhotonMappingRenderer::NoGather
                            | PhotonMappingRenderer::AllowMultiray
                            //| PhotonMappingRenderer::PhotonVisualize
                            );

    renderer->setMaximumDepth(10);
    renderer->setMaximumMultirayDepth(2);

    if (argc == 2)
        renderer->loadPhotonMap(argv[1]);
    else{
        renderer->buildPhotonMap();
        renderer->savePhotonMap("photonMap.txt");
    }

    film->setDirectDisplay(true);
    renderer->render();
    film->saveImage("output.png");
}

void wine(int argc, char **argv){

    Scene *scene = new Scene;
    Camera *camera = new PerspectiveCamera;
    Film *film = new Film(300, -200, 200, -200, 200);
    camera->setPosition(15, -15, 15, 0, -3, 5, 0, 0, 1);

    Cuboid *floor1 = new Cuboid(0, 0, -1, 100, 100, 2);
    MeshObject *glass2 = new MeshObject("glass.obj");
    glass2->rotate(90, 1, 0, 0);
    glass2->translate(0, 0, -0.898);
    //glass2->scale(1.5);
    MeshObject *wine3 = new MeshObject("wine.obj", -1);
    wine3->rotate(90, 1, 0, 0);
    wine3->translate(0, 0, -0.898);
    //wine3->scale(1.5);

    BitmapTexture *texture1 = new BitmapTexture("woodsq.png");

    LambertianBSDF *bsdf1 = new LambertianBSDF(1, texture1);
    FresnelBSDF *bsdf2 = new FresnelBSDF();

    Material *material1 = new Material(bsdf1);
    Material *material2 = new Material(bsdf2, 1.52);
    Material *material3 = new Material(bsdf2, 1.333, RGBColor(0.9, 0.5, 0.2));

    floor1->material = material1;
    glass2->material = material2;
    wine3->material = material3;

    //PointLight *light1 = new PointLight(0, 30, 30, 1, 5000);
    SquareLight *light1 = new SquareLight(0, 30, 30, 0, -1, -1, 0, 0, 1, 4, 4, 1, 1500);

    scene->addObject(floor1);
    scene->addObject(glass2);
    scene->addObject(wine3);
    scene->addLight(light1);

    PhotonMappingRenderer *renderer = new PhotonMappingRenderer(scene, camera, film, 1);
    renderer->setPhotonNumber(10000, 1000, 10, 10);
    renderer->setQuality(1, 16);
    renderer->setRenderMode(0
                            | PhotonMappingRenderer::DirectComponent
                            //| PhotonMappingRenderer::IndirectComponent
                            | PhotonMappingRenderer::SpecularComponent
                            | PhotonMappingRenderer::CausticComponent
                            //| PhotonMappingRenderer::NoGather
                            | PhotonMappingRenderer::AllowMultiray
                            //| PhotonMappingRenderer::PhotonVisualize
                            );
    //renderer->setRenderMode(PhotonMappingRenderer::NoGather | PhotonMappingRenderer::SpecularComponent);

    renderer->setMaximumDepth(10);
    renderer->setMaximumMultirayDepth(5);

    if (argc == 2)
        renderer->loadPhotonMap(argv[1]);
    else{
        renderer->buildPhotonMap();
        renderer->savePhotonMap("photonMap.txt");
    }

    film->setDirectDisplay(true);
    renderer->render();
    film->saveImage("output.png");
}

void finalRender(int argc, char **argv){
    Scene *scene = new Scene;
    Camera *camera = new PerspectiveCamera;
    Film *film = new Film(250, -250, 250, -250, 250);
    //Film *film = new Film(250, 70, 80, 70, 80);
    camera->setPosition(20, 20, 15, 0, 0, 0, 0, 0, 1);
    //camera->setDofEnabled(true);
    //camera->setAperture(1);
    //camera->focus(5, 5, 2);

    Cuboid *floor1 = new Cuboid(0, 0, -1, 50, 50, 2);
    Cuboid *walln2 = new Cuboid(0, -16, 15, 50, 2, 30);
    Cuboid *wallw3 = new Cuboid(26, 0, 15, 2, 50, 30);
    Cuboid *walls4 = new Cuboid(0, 26, 15, 50, 2, 30);
    Cuboid *walle5 = new Cuboid(-26, 0, 15, 2, 50, 30);
    Cuboid *ceil6 = new Cuboid(0, 0, 31, 50, 50, 2);
    MeshObject *glass7 = new MeshObject("glass.obj");
    glass7->rotate(90, 1, 0, 0);
    glass7->translate(-5, 5, -0.898);
    glass7->scale(1.5);
    MeshObject *wine8 = new MeshObject("wine.obj", -1);
    wine8->rotate(90, 1, 0, 0);
    wine8->translate(-5, 5, -0.898);
    wine8->scale(1.5);
    MeshObject *bunny9 = new MeshObject("bunny.obj");
    bunny9->rotate(90, 1, 0, 0);
    bunny9->translate(0, 0, -0.034);
    bunny9->rotate(180, 0, 0, 1);
    bunny9->scale(100);
    bunny9->translate(5, 5, 0);

    BitmapTexture *texture1 = new BitmapTexture("woodsq.png");
    PerlinNoise3D *texture9 = new PerlinNoise3D(7, 0.5, 12345, "marble02.jpg", 5, 5, 5, 5);

    LambertianBSDF *bsdf1 = new LambertianBSDF(1, texture1);
    LambertianBSDF *bsdf2 = new LambertianBSDF(0.8);
    FresnelBSDF *bsdf7 = new FresnelBSDF;
    PhaseIsotropic *bsdf9 = new PhaseIsotropic(1, texture9);

    Material *material1 = new Material(bsdf1);
    Material *material2 = new Material(bsdf2);
    Material *material7 = new Material(bsdf7, 1.52);
    Material *material8 = new Material(bsdf7, 1.333, RGBColor(0.87, 0.42, 0.56));
    Material *material9 = new Material(bsdf7, 1.4, 1, bsdf9, 0.005);

    floor1->material = material1;
    walln2->material = material2;
    wallw3->material = material2;
    walls4->material = material2;
    walle5->material = material2;
    ceil6->material = material2;
    glass7->material = material7;
    wine8->material = material8;
    bunny9->material = material9;

    //SquareLight *light1 = new SquareLight(0, 24.9, 20, 0, -1, 0, 0, 0, 1, 5, 5, 1, 15000);
    PointLight *light1 = new PointLight(0, 24.9, 20, 1, 30000);

    scene->addObject(floor1);
    scene->addObject(walln2);
    scene->addObject(wallw3);
    scene->addObject(walls4);
    scene->addObject(walle5);
    scene->addObject(ceil6);
    //scene->addObject(glass7);
    //scene->addObject(wine8);
    scene->addObject(bunny9);
    scene->addLight(light1);

    PhotonMappingRenderer *renderer = new PhotonMappingRenderer(scene, camera, film, 4);
    renderer->setPhotonNumber(100000, 0, 100, 10);
    renderer->setQuality(1, 16);
    renderer->setRenderMode(0
                            | PhotonMappingRenderer::DirectComponent
                            | PhotonMappingRenderer::IndirectComponent
                            | PhotonMappingRenderer::SpecularComponent
                            | PhotonMappingRenderer::CausticComponent
                            //| PhotonMappingRenderer::NoGather
                            | PhotonMappingRenderer::AllowMultiray
                            //| PhotonMappingRenderer::PhotonVisualize
                            );
    //renderer->setRenderMode(PhotonMappingRenderer::NoGather | PhotonMappingRenderer::SpecularComponent);

    renderer->setMaximumDepth(10);
    renderer->setMaximumMultirayDepth(4);

    if (argc == 2)
        renderer->loadPhotonMap(argv[1]);
    else{
        renderer->buildPhotonMap();
        renderer->savePhotonMap("photonMap.txt");
    }

    film->setDirectDisplay(true);
    renderer->render();
    film->saveImage("output.png");
}

void globalLighting(int argc, char **argv){
    srand(time(0));
    Scene *scene = new Scene;
    Camera *camera = new PerspectiveCamera;
    Film *film = new Film(500, -400, 400, -400, 400);
    //Film *film = new Film(125, -100, 100, -100, 100);
    camera->setPosition(0, 17, 0, 0, 0, 0, 0, 0, 1);

    Cuboid *cuboid1 = new Cuboid(0, 0, -11, 20, 20, 2);
    Cuboid *cuboid2 = new Cuboid(11, 0, 0, 2, 20, 20);
    Cuboid *cuboid3 = new Cuboid(0, 0, 11, 20, 20, 2);
    Cuboid *cuboid4 = new Cuboid(-11, 0, 0, 2, 20, 20);
    Cuboid *cuboid5 = new Cuboid(0, -11, 0, 20, 2, 20);
    MeshObject *bunny6 = new MeshObject("bunny.obj");
    bunny6->rotate(90, 1, 0, 0);
    bunny6->translate(0, 0, -0.034);
    bunny6->rotate(180, 0, 0, 1);
    bunny6->scale(80);
    bunny6->translate(-2, -3, -10);

    PerlinNoise3D *texture6 = new PerlinNoise3D(7, 0.6, 123456, "marble06.png", 10, 10, 10, 1);

    LambertianBSDF *bsdf1 = new LambertianBSDF(RGBColor(0.7, 0.7, 0.3));
    LambertianBSDF *bsdf2 = new LambertianBSDF(RGBColor(0.3, 0.7, 0.3));
    LambertianBSDF *bsdf3 = new LambertianBSDF(RGBColor(0.3, 0.3, 0.7));
    LambertianBSDF *bsdf4 = new LambertianBSDF(RGBColor(0.7, 0.3, 0.3));
    LambertianBSDF *bsdf5 = new LambertianBSDF(RGBColor(0.7, 0.7, 0.7));
    FresnelBSDF *bsdf6a = new FresnelBSDF;
    PhaseIsotropic *bsdf6b = new PhaseIsotropic(1, texture6);
    //SpecularBSDF *bsdf6a = new SpecularBSDF;
    //PhongBSDF *bsdf6b = new PhongBSDF(0, RGBColor(0.1, 0.1, 0.4));
    //FresnelBlendBSDF *bsdf6 = new FresnelBlendBSDF(bsdf6a, bsdf6b);

    Material *material1 = new Material(bsdf1);
    Material *material2 = new Material(bsdf2);
    Material *material3 = new Material(bsdf3);
    Material *material4 = new Material(bsdf4);
    Material *material5 = new Material(bsdf5);
    Material *material6 = new Material(bsdf6a, 1.5, 1, bsdf6b, 0.005);
    //Material *material6 = new Material(bsdf6, 1.5);

    cuboid1->material = material1;
    cuboid2->material = material2;
    cuboid3->material = material3;
    cuboid4->material = material4;
    cuboid5->material = material5;
    bunny6->material = material6;

    //PointLight *light1 = new PointLight(0, 0, 0, 1, 1000);
    SquareLight *light1 = new SquareLight(0, 0, 9.999, 0, 0, -1, 0, 1, 0, 4, 4, 1, 2000);

    scene->addObject(cuboid1);
    scene->addObject(cuboid2);
    scene->addObject(cuboid3);
    scene->addObject(cuboid4);
    scene->addObject(cuboid5);
    scene->addObject(bunny6);
    scene->addLight(light1);

    PhotonMappingRenderer *renderer = new PhotonMappingRenderer(scene, camera, film, 4);
    renderer->setPhotonNumber(100000, 0, 100, 100);
    renderer->setQuality(1, 16);
    renderer->setRenderMode(0
                            | PhotonMappingRenderer::DirectComponent
                            | PhotonMappingRenderer::IndirectComponent
                            | PhotonMappingRenderer::SpecularComponent
                            //| PhotonMappingRenderer::CausticComponent
                            //| PhotonMappingRenderer::NoGather
                            | PhotonMappingRenderer::AllowMultiray
                            //| PhotonMappingRenderer::PhotonVisualize
                            );

    renderer->setMaximumDepth(10);
    renderer->setMaximumMultirayDepth(2);

    if (argc == 2)
        renderer->loadPhotonMap(argv[1]);
    else{
        renderer->buildPhotonMap();
        renderer->savePhotonMap("photonMap.txt");
    }

    film->setDirectDisplay(true);
    renderer->render();
    film->saveImage("output.png");
}

void texture_CSG_DOF(int argc, char **argv){
    Scene *scene = new Scene;
    Camera *camera = new PerspectiveCamera;
    Film *film = new Film(300, -200, 200, -150, 100);
    camera->setPosition(20, 5, 6, 0, 0, 0, 0, 0, 1);
    camera->setDofEnabled(true);
    camera->setAperture(1);
    camera->focus(5, 0, 0);

    Cuboid *cuboid1 = new Cuboid(0, 0, -4, 100, 100, 2);
    Sphere *sphere2 = new Sphere(0, 0, 0, 3);
        sphere2->rotate(-30, 0, 0, 1);
        sphere2->rotate(30, 1, 0, 0);
        sphere2->translate(-5, 6, 0);
    Sphere *sphere3 = new Sphere(0, 0, 0, 3);
        sphere3->rotate(30, 0, 0, 1);
        sphere3->rotate(-30, 1, 0, 0);
        sphere3->translate(-5, -6, 0);
    PrimitivePtr csg4a = new Sphere(5, 0, 0, 3);
    PrimitivePtr csg4b = new Cuboid(5, 0, 0, 4.8, 4.8, 4.8);
    PrimitivePtr csg4c = new Cylinder(5, 0, 0, 1.5, 4.81);
    PrimitivePtr csg4d = new Cylinder(0, 0, 0, 1.5, 4.81);
    csg4d->rotate(90, 1, 0, 0);
    csg4d->translate(5, 0, 0);
    PrimitivePtr csg4e = new Cylinder(0, 0, 0, 1.5, 4.81);
    csg4e->rotate(90, 0, 1, 0);
    csg4e->translate(5, 0, 0);
    CSGObject *csg4 = csg4a * csg4b - csg4c - csg4d - csg4e;
    csg4->setChildCSG();

    BitmapTexture *texture2 = new BitmapTexture("ball10.png");
    BitmapTexture *texture3 = new BitmapTexture("ball13.png");
    LambertianBSDF *bsdf1 = new LambertianBSDF(RGBColor(0.1, 1, 0.1));
    SpecularBSDF *bsdf2a = new SpecularBSDF(1);
    LambertianBSDF *bsdf2b = new LambertianBSDF(1, texture2);
    LambertianBSDF *bsdf3b = new LambertianBSDF(1, texture3);
    LambertianBSDF *bsdf4b = new LambertianBSDF(RGBColor(0.8, 0.8, 0.9));
    FresnelBlendBSDF *bsdf2 = new FresnelBlendBSDF(bsdf2a, bsdf2b);
    FresnelBlendBSDF *bsdf3 = new FresnelBlendBSDF(bsdf2a, bsdf3b);
    FresnelBlendBSDF *bsdf4 = new FresnelBlendBSDF(bsdf2a, bsdf4b);
    Material *material1 = new Material(bsdf1);
    Material *material2 = new Material(bsdf2, 1.5);
    Material *material3 = new Material(bsdf3, 1.5);
    Material *material4 = new Material(bsdf4, 1.5);

    cuboid1->material = material1;
    sphere2->material = material2;
    sphere3->material = material3;
    csg4a->material = material4;
    csg4b->material = material4;
    csg4c->material = material4;
    csg4d->material = material4;
    csg4e->material = material4;

    SquareLight *light1 = new SquareLight(0, 0, 50, 0, 0, -1, 1, 0, 0, 150, 150, 1, 50000);

    scene->addObject(cuboid1);
    scene->addObject(sphere2);
    scene->addObject(sphere3);
    scene->addObject(csg4);
    scene->addLight(light1);

    PhotonMappingRenderer *renderer = new PhotonMappingRenderer(scene, camera, film, 16);
    renderer->setPhotonNumber(0, 0, 100, 100);
    renderer->setQuality(1, 8);
    renderer->setRenderMode(0
                            | PhotonMappingRenderer::DirectComponent
                            //| PhotonMappingRenderer::IndirectComponent
                            | PhotonMappingRenderer::SpecularComponent
                            | PhotonMappingRenderer::CausticComponent
                            //| PhotonMappingRenderer::NoGather
                            | PhotonMappingRenderer::AllowMultiray
                            //| PhotonMappingRenderer::PhotonVisualize
                            );

    renderer->setMaximumDepth(10);
    renderer->setMaximumMultirayDepth(2);

    if (argc == 2)
        renderer->loadPhotonMap(argv[1]);
    else{
        renderer->buildPhotonMap();
        renderer->savePhotonMap("photonMap.txt");
    }

    film->setDirectDisplay(true);
    renderer->render();
    film->saveImage("output.png");
}

void cornell_flood(int argc, char **argv){
    srand(time(0));
    Scene *scene = new Scene;
    Camera *camera = new PerspectiveCamera;
    Film *film = new Film(500, -400, 400, -400, 400);
    //Film *film = new Film(250, -200, 200, -200, 200);
    //Film *film = new Film(125, -100, 100, -100, 100);
    //Film *film = new Film(250, 0, 50, -50, 0);
    camera->setPosition(0, 17, 0, 0, 0, 0, 0, 0, 1);

    Cuboid *cuboid1 = new Cuboid(0, 0, -11, 20, 20, 2);
    Cuboid *cuboid2 = new Cuboid(11, 0, 0, 2, 20, 20);
    Cuboid *cuboid3 = new Cuboid(0, 0, 11, 20, 20, 2);
    Cuboid *cuboid4 = new Cuboid(-11, 0, 0, 2, 20, 20);
    Cuboid *cuboid5 = new Cuboid(0, -11, 0, 20, 2, 20);
    Cuboid *cuboid6 = new Cuboid(0, 10.2, 0, 20, 0.4, 20);
    MeshObject *water7 = new MeshObject("water.obj", -1);
    water7->scale(0.2, 0.2, 0.2);
    //water7->rotate(180.01, 1, 0, 0);
    //water7->rotate(0.01, 0, 1, 0);
    water7->translate(0, 0, 3);
    Sphere *sphere8 = new Sphere(-2, -5, -3, 5);

    LambertianBSDF *bsdf1 = new LambertianBSDF(RGBColor(0.7, 0.7, 0.3));
    LambertianBSDF *bsdf2 = new LambertianBSDF(RGBColor(0.3, 0.7, 0.3));
    LambertianBSDF *bsdf3 = new LambertianBSDF(RGBColor(0.3, 0.3, 0.7));
    LambertianBSDF *bsdf4 = new LambertianBSDF(RGBColor(0.7, 0.3, 0.3));
    LambertianBSDF *bsdf5 = new LambertianBSDF(RGBColor(0.7, 0.7, 0.7));
    FresnelBSDF *bsdf6 = new FresnelBSDF;
    //LambertianBSDF *bsdf7 = new LambertianBSDF(RGBColor(0.7, 0.7, 0.7));
    FresnelBSDF *bsdf7 = new FresnelBSDF;
    SpecularBSDF *bsdf8 = new SpecularBSDF;

    Material *material1 = new Material(bsdf1);
    Material *material2 = new Material(bsdf2);
    Material *material3 = new Material(bsdf3);
    Material *material4 = new Material(bsdf4);
    Material *material5 = new Material(bsdf5);
    Material *material6 = new Material(bsdf6, 1.62);
    Material *material7 = new Material(bsdf7, 1.333);
    Material *material8 = new Material(bsdf8);

    cuboid1->material = material1;
    cuboid2->material = material2;
    cuboid3->material = material3;
    cuboid4->material = material4;
    cuboid5->material = material5;
    cuboid6->material = material6;
    water7->material = material7;
    sphere8->material = material8;

    SquareLight *light1 = new SquareLight(0, 0, 9.999, 0, 0, -1, 0, 1, 0, 4, 4, 1, 2000);

    scene->addObject(cuboid1);
    scene->addObject(cuboid2);
    scene->addObject(cuboid3);
    scene->addObject(cuboid4);
    scene->addObject(cuboid5);
    scene->addObject(cuboid6);
    scene->addObject(water7);
    scene->addObject(sphere8);
    scene->addLight(light1);

    PhotonMappingRenderer *renderer = new PhotonMappingRenderer(scene, camera, film, 16);
    renderer->setPhotonNumber(10000000, 10000000, 100, 100);
    renderer->setQuality(1, 16);
    renderer->setRenderMode(0
                            | PhotonMappingRenderer::DirectComponent
                            | PhotonMappingRenderer::IndirectComponent
                            | PhotonMappingRenderer::SpecularComponent
                            | PhotonMappingRenderer::CausticComponent
                            //| PhotonMappingRenderer::NoGather
                            | PhotonMappingRenderer::AllowMultiray
                            //| PhotonMappingRenderer::PhotonVisualize
                            );

    renderer->setMaximumDepth(10);
    renderer->setMaximumMultirayDepth(2);

    if (argc == 2)
        renderer->loadPhotonMap(argv[1]);
    else{
        renderer->buildPhotonMap();
        renderer->savePhotonMap("photonMap.txt");
    }

    film->setDirectDisplay(false);
    renderer->render();
    film->saveImage("output.png");
}

void specular_caustic(int argc, char **argv){
    Scene *scene = new Scene;
    Camera *camera = new PerspectiveCamera;
    Film *film = new Film(700, -450, 450, -240, 210);
    camera->setPosition(25, 25, 25, 0, 0, 15, 0, 0, 1);

    Cuboid *cuboid1 = new Cuboid(0, 0, -1, 100, 100, 2);
    MeshObject *horse2 = new MeshObject("horse.obj");
    horse2->rotate(-90, 0, 0, 1);
    horse2->translate(0, 0, 0.8316);
    horse2->scale(10);
    horse2->translate(0, -20, 0);
    Cuboid *cuboid3 = new Cuboid(0, -40, 15, 100, 2, 30);
    Cuboid *cuboid4 = new Cuboid(-40, 0, 15, 2, 100, 30);
    MeshObject *dragon5 = new MeshObject("dragon.obj");
    dragon5->rotate(90, 1, 0, 0);
    dragon5->translate(0, 0, 0.704);
    dragon5->rotate(90, 0, 0, 1);
    dragon5->scale(10);
    dragon5->translate(-20, 0, 0);
    Cuboid *cuboid6 = new Cuboid(0, 40, 15, 100, 2, 30);
    Cuboid *cuboid7 = new Cuboid(40, 0, 15, 2, 100, 30);

    CheckerColor *texture1 = new CheckerColor(0, 1, 25, 25, 0, 0);

    LambertianBSDF *bsdf1 = new LambertianBSDF(1, texture1);
    FresnelBSDF *bsdf2 = new FresnelBSDF;
    LambertianBSDF *bsdf3 = new LambertianBSDF;
    SpecularBSDF *bsdf5 = new SpecularBSDF(RGBColor(0.5, 0.5, 1));

    Material *material1 = new Material(bsdf1);
    Material *material2 = new Material(bsdf2, 1.52, RGBColor(0.95, 0.95, 0.8));
    Material *material3 = new Material(bsdf3);
    Material *material5 = new Material(bsdf5);

    cuboid1->material = material1;
    horse2->material = material2;
    cuboid3->material = material3;
    cuboid4->material = material3;
    dragon5->material = material5;
    cuboid6->material = material3;
    cuboid7->material = material3;

    //SquareLight *light1 = new SquareLight(0, 30, 30, 0, -1, -1, 0, 0, 1, 5, 5, 1, 10000);
    PointLight *light1 = new PointLight(0, 0, 15, 1, 30000);

    scene->addObject(cuboid1);
    scene->addObject(horse2);
    scene->addObject(cuboid3);
    scene->addObject(cuboid4);
    scene->addObject(dragon5);
    scene->addLight(light1);
    scene->addObject(cuboid6);
    scene->addObject(cuboid7);

    PhotonMappingRenderer *renderer = new PhotonMappingRenderer(scene, camera, film, 4);
    renderer->setPhotonNumber(0, 1000000, 100, 100);
    renderer->setQuality(1, 16);
    renderer->setRenderMode(0
                            | PhotonMappingRenderer::DirectComponent
                            //| PhotonMappingRenderer::IndirectComponent
                            | PhotonMappingRenderer::SpecularComponent
                            | PhotonMappingRenderer::CausticComponent
                            //| PhotonMappingRenderer::NoGather
                            | PhotonMappingRenderer::AllowMultiray
                            //| PhotonMappingRenderer::PhotonVisualize
                            );

    renderer->setMaximumDepth(10);
    renderer->setMaximumMultirayDepth(10);

    if (argc == 2)
        renderer->loadPhotonMap(argv[1]);
    else{
        renderer->buildPhotonMap();
        renderer->savePhotonMap("photonMap.txt");
    }

    film->setDirectDisplay(true);
    renderer->render();
    film->saveImage("output.png");
}

void bump_test(int argc, char **argv){
    Scene *scene = new Scene;
    Camera *camera = new PerspectiveCamera;
    camera->setPosition(20, 50, 20, 0, 0, 1, 0, 0, 1);
    camera->setDofEnabled(true);
    camera->setAperture(1);
    camera->focus(0, 0, 1);
    //Film *film = new Film(1250, -160, 160, -90, 90);
    //Film *film = new Film(2500, -320, 320, -180, 180);
    //Film *film = new Film(5000, -640, 640, -360, 360);
    Film *film = new Film(7500, -960, 960, -540, 540);

    Cuboid *table1 = new Cuboid(0, 0, -1, 100, 100, 2);
    table1->rotate(30, 0, 0, 1);
    MeshObject *teacup2 = new MeshObject("teacup_01a.obj", -1, false);
    teacup2->rotate(90, 1, 0, 0);
    teacup2->rotate(-15, 0, 0, 1);
    teacup2->scale(20);
    teacup2->translate(2, -2, 0);
    MeshObject *teacup3 = new MeshObject("teacup_01b.obj", -1);
    teacup3->rotate(90, 1, 0, 0);
    teacup3->rotate(-15, 0, 0, 1);
    teacup3->scale(20);
    teacup3->translate(2, -2, 0);
    MeshObject *tea4 = new MeshObject("tea.obj", -2, false);
    tea4->rotate(90, 1, 0, 0);
    tea4->scale(20);
    tea4->translate(2, -2, 0);
    MeshObject *spoon5 = new MeshObject("spoon.obj");
    spoon5->rotate(90, 1, 0, 0);
    spoon5->scale(20);
    spoon5->translate(-2, 2, 0);

    BitmapTexture *texture1 = new BitmapTexture("texture_textile_2b.png", 50, 50);
    BitmapBumpMapping *bump1 = new BitmapBumpMapping("bump_textile_1.jpg", 0.1, 200, 200);
    //BitmapTexture *texture3 = new BitmapTexture("sky03.exr", 1, 1, true);
    BitmapTexture *texture3 = new BitmapTexture("sky03b.png");

    LambertianBSDF *bsdf1 = new LambertianBSDF(1, texture1, bump1);
    ///*
    SpecularBSDF *bsdf2a = new SpecularBSDF;
    LambertianBSDF *bsdf2b = new LambertianBSDF(RGBColor(0.9, 0.9, 0.8));
    FresnelBlendBSDF *bsdf2 = new FresnelBlendBSDF(bsdf2a, bsdf2b);
    FresnelBSDF *bsdf3 = new FresnelBSDF;
    SpecularBSDF *bsdf4a = new SpecularBSDF;
    LambertianBSDF *bsdf4b = new LambertianBSDF(RGBColor(0.8, 0.4, 0.2));
    FresnelBlendBSDF *bsdf4 = new FresnelBlendBSDF(bsdf4a, bsdf4b);
    //*/
    //FresnelBSDF *bsdf2 = new FresnelBSDF;
    //FresnelBSDF *bsdf4 = new FresnelBSDF;
    SpecularBSDF *bsdf5 = new SpecularBSDF(0.5);

    Material *material1 = new Material(bsdf1);
    Material *material2 = new Material(bsdf2, 1.5);
    Material *material3 = new Material(bsdf3, 1.5);
    //Material *material4 = new Material(bsdf4, 1.33);
    Material *material4 = new Material(bsdf3, 1.33, RGBColor(0.8, 0.4, 0.2));
    Material *material5 = new Material(bsdf5);

    table1->material = material1;
    teacup2->material = material2;
    teacup3->material = material3;
    tea4->material = material4;
    spoon5->material = material5;

    /*
    SquareLight *light1 = new SquareLight(0, 30, 30, 0, -1, -1, 0, 0, 1, 10, 10, 1, 10000);
    SquareLight *light2 = new SquareLight(0, 0, 100, 0, 0, -1, 0, 1, 0, 100, 100, 1, 10000);
    */
    EnviromentLight *light3 = new EnviromentLight(Point(0, 0, 0), 20, texture3, 1, 6000, 1000);

    scene->addObject(table1);
    scene->addObject(teacup2);
    scene->addObject(teacup3);
    scene->setEnviromentLight(light3);
    scene->addObject(tea4);
    scene->addObject(spoon5);

    PhotonMappingRenderer *renderer = new PhotonMappingRenderer(scene, camera, film, 12);
    renderer->setPhotonNumber(0, 5000000, 100, 50);
    renderer->setQuality(1, 1);
    renderer->setRenderMode(0
                            | PhotonMappingRenderer::DirectComponent
                            //| PhotonMappingRenderer::IndirectComponent
                            | PhotonMappingRenderer::SpecularComponent
                            | PhotonMappingRenderer::CausticComponent
                            //| PhotonMappingRenderer::NoGather
                            | PhotonMappingRenderer::AllowMultiray
                            //| PhotonMappingRenderer::PhotonVisualize
                            );

    renderer->setMaximumDepth(10);
    renderer->setMaximumMultirayDepth(3);

    if (argc == 2)
        renderer->loadPhotonMap(argv[1]);
    else{
        renderer->buildPhotonMap();
        renderer->savePhotonMap("photonMap.txt");
    }

    film->setDirectDisplay(true);
    renderer->render();
    film->saveImage("output.png");
    film->saveImage("output.exr", false);
}

void fog(int argc, char **argv) {
    ///*
    Scene *scene = new Scene;
    Camera *camera = new PerspectiveCamera;
    camera->setPosition(90, -30, 25, 0, 3, 15, 0, 0, 1);
    camera->setDofEnabled(true);
    camera->setAperture(4);
    camera->focus(0, 0, 15);
    Film *film = new Film(800, -400, 400, -250, 200);
    //Film *film = new Film(200, -100, 100, -63, 50);

    Cuboid *ground1 = new Cuboid(0, 0, -1, 1000, 1000, 2);
    Sphere *sphere2 = new Sphere(0, 0, 15, 12, 1);
    //Cuboid *fog3 = new Cuboid(0, 0, 30, 10, 10, 10);
    Cuboid *fog3 = new Cuboid(0, 0, 25, 100, 100, 49.9);

    CheckerColor *texture1 = new CheckerColor(RGBColor(0.7, 0.4, 0.1), RGBColor(0.4, 0.1, 0.7), 100, 100, 0, 0);

    LambertianBSDF *bsdf1 = new LambertianBSDF(1, texture1);
    PhongBSDF *bsdf2a = new PhongBSDF(0, RGBColor(0.1, 0.6, 0.1));
    SpecularBSDF *bsdf2b = new SpecularBSDF;
    //FresnelBlendBSDF *bsdf2 = new FresnelBlendBSDF(bsdf2b, bsdf2a);
    FresnelBSDF *bsdf2 = new FresnelBSDF;
    NullBSDF *bsdf3a = new NullBSDF;
    PhaseIsotropic *bsdf3b = new PhaseIsotropic(0.6);

    Material *material1 = new Material(bsdf1);
    Material *material2 = new Material(bsdf2, 1.4, RGBColor(0.8, 0.97, 0.8));
    Material *material3 = new Material(bsdf3a, 1, 1, bsdf3b, 0.99, 1);

    ground1->material = material1;
    sphere2->material = material2;
    fog3->material = material3;

    SpotLight *light4 = new SpotLight(0, -75, 150, 0, 0, 15, 5, 3, 1, 20000);
    //PointLight *light4 = new PointLight(0, -20, 45, 1, 30000);
    //SquareLight *light4 = new SquareLight(0, 0, 100, 0, 0, -1, 1, 0, 0, 10, 10, 1, 10000);
    EnviromentLight *light5 = new EnviromentLight(Point(0, 0, 0), 100, 0, 1, 50000, 1000);

    scene->addObject(ground1);
    scene->addObject(sphere2);
    scene->addObject(fog3);
    scene->addLight(light4);
    scene->setEnviromentLight(light5);

    PhotonMappingRenderer *renderer = new PhotonMappingRenderer(scene, camera, film, 16);
    renderer->setPhotonNumber(100000, 100000, 100, 100);
    renderer->setQuality(1, 1);
    renderer->setRenderMode(0
                            | PhotonMappingRenderer::DirectComponent
                            | PhotonMappingRenderer::IndirectComponent
                            | PhotonMappingRenderer::SpecularComponent
                            | PhotonMappingRenderer::CausticComponent
                            //| PhotonMappingRenderer::NoGather
                            | PhotonMappingRenderer::AllowMultiray
                            //| PhotonMappingRenderer::PhotonVisualize
                            );

    renderer->setMaximumDepth(10);
    renderer->setMaximumMultirayDepth(10);

    renderer->buildPhotonMap();

    film->setDirectDisplay(true);
    renderer->render();
    film->saveImage("output.png");
    //*/
}

void glass_test() {
    Scene *scene = new Scene;
    Camera *camera = new PerspectiveCamera;
    camera->setPosition(40, -25, 10, 0, 0, 0, 0, 0, 1);
    Film *film = new Film(700, -400, 560, -300, 300);

    Sphere *sphere1 = new Sphere(-18, 0, 5, 5);
    Sphere *sphere2 = new Sphere(-6, 0, 5, 5);
    Sphere *sphere3 = new Sphere(6, 0, 5, 5);
    Sphere *sphere4 = new Sphere(18, 0, 5, 5);
    Cuboid *cuboid5 = new Cuboid(0, 0, -1, 100, 100, 2);

    FresnelBSDF *bsdf1 = new FresnelBSDF;
    LambertianBSDF *bsdf2 = new LambertianBSDF(0.4);

    Material *material1 = new Material(bsdf1, 1.52, RGBColor(1, 0.95, 0.95));
    Material *material2 = new Material(bsdf1, 1.52, RGBColor(1, 1, 0.95));
    Material *material3 = new Material(bsdf1, 1.52, RGBColor(0.95, 1, 0.95));
    Material *material4 = new Material(bsdf1, 1.52, RGBColor(0.95, 0.95, 1));
    Material *material5 = new Material(bsdf2);

    sphere1->material = material1;
    sphere2->material = material2;
    sphere3->material = material3;
    sphere4->material = material4;
    cuboid5->material = material5;

    SquareLight *light1 = new SquareLight(0, 20, 30, 0, -20, -30, 0, 0, 1, 5, 5, 1, 5000);

    scene->addObject(sphere1);
    scene->addObject(sphere2);
    scene->addObject(sphere3);
    scene->addObject(sphere4);
    scene->addObject(cuboid5);
    scene->addLight(light1);

    PhotonMappingRenderer *renderer = new PhotonMappingRenderer(scene, camera, film, 4);
    renderer->setPhotonNumber(10000, 100000, 100, 100);
    //renderer->setPhotonNumber(1000, 1000, 100, 100);
    renderer->setQuality(1, 64);
    renderer->setRenderMode(0
                            | PhotonMappingRenderer::DirectComponent
                            //| PhotonMappingRenderer::IndirectComponent
                            | PhotonMappingRenderer::SpecularComponent
                            | PhotonMappingRenderer::CausticComponent
                            //| PhotonMappingRenderer::NoGather
                            | PhotonMappingRenderer::AllowMultiray
                            //| PhotonMappingRenderer::PhotonVisualize
                            );

    renderer->setMaximumDepth(10);
    renderer->setMaximumMultirayDepth(10);

    renderer->buildPhotonMap();

    film->setDirectDisplay(true);
    renderer->render();
    film->saveImage("output.png");
    //*/
}

void cornell_simple(int argc, char **argv){
    srand(time(0));
    Scene *scene = new Scene;
    Camera *camera = new PerspectiveCamera;
    Film *film = new Film(1150, -400, 400, -400, 400);
    camera->setPosition(278, 273, -800, 278, 273, 0, 0, 1, 0);

    double length = 553.6;
    double height = 548.8;
    double depth = 559.2;
    double lightX = 278;
    double lightZ = 279.5;
    double lightWidth = 130;
    double lightHeight = 105;
    double blockBaseSize = 165;
    double blockRotation = 17;
    double block1X = 185.5;
    double block1Z = 169;
    double block2X = 368.5;
    double block2Z = 351.25;

    SquareLight *light1 = new SquareLight(lightX, height - 0.001, lightZ, 0, -1, 0, 0, 0, 1, lightWidth, lightHeight, RGBColor(1.0, 0.55, 0.2), 2 * 1e6);

    Cuboid *floor1 = new Cuboid(length / 2, -0.001, depth / 2, length, 0.002, depth);
    Cuboid *ceil2  = new Cuboid(length / 2, height + 0.001, depth / 2, length, 0.002, depth);
    Cuboid *back3  = new Cuboid(length / 2, height / 2, depth + 0.001, length, height, 0.002);
    Cuboid *right4 = new Cuboid(-0.001, height / 2, depth / 2, 0.002, height, depth);
    Cuboid *left5  = new Cuboid(length + 0.001, height / 2, depth / 2, 0.001, height, depth);
    Cuboid *block6 = new Cuboid(0, blockBaseSize / 2, 0, blockBaseSize, blockBaseSize, blockBaseSize);
    block6->rotate(-17, 0, 1, 0);
    block6->translate(block1X, 0, block1Z);
    Cuboid *block7 = new Cuboid(0, blockBaseSize, 0, blockBaseSize, blockBaseSize * 2, blockBaseSize);
    block7->rotate(17, 0, 1, 0);
    block7->translate(block2X, 0, block2Z);

    LambertianBSDF *lambertianRed = new LambertianBSDF(RGBColor(0.6, 0.07, 0.05) * 1);
    LambertianBSDF *lambertianGreen = new LambertianBSDF(RGBColor(0.21, 0.59, 0.16) * 1);
    LambertianBSDF *lambertianWhite = new LambertianBSDF(1);

    Material *red = new Material(lambertianRed);
    Material *green = new Material(lambertianGreen);
    Material *white = new Material(lambertianWhite);

    floor1->material = white;
    ceil2->material = white;
    back3->material = white;
    right4->material = green;
    left5->material = red;
    block6->material = white;
    block7->material = white;

    scene->addObject(floor1);
    scene->addObject(ceil2);
    scene->addObject(back3);
    scene->addObject(right4);
    scene->addObject(left5);
    scene->addObject(block6);
    scene->addObject(block7);
    scene->addLight(light1);

    PhotonMappingRenderer *renderer = new PhotonMappingRenderer(scene, camera, film, 8);
    renderer->setPhotonNumber(100000, 0, 100, 100);
    renderer->setQuality(16, 16);
    renderer->setRenderMode(0
                            | PhotonMappingRenderer::DirectComponent
                            | PhotonMappingRenderer::IndirectComponent
                            | PhotonMappingRenderer::SpecularComponent
                            | PhotonMappingRenderer::CausticComponent
                            //| PhotonMappingRenderer::NoGather
                            | PhotonMappingRenderer::AllowMultiray
                            //| PhotonMappingRenderer::PhotonVisualize
                            );

    renderer->setMaximumDepth(10);
    renderer->setMaximumMultirayDepth(2);

    if (argc == 2)
        renderer->loadPhotonMap(argv[1]);
    else{
        renderer->buildPhotonMap();
        renderer->savePhotonMap("photonMap.txt");
    }

    film->setDirectDisplay(true);
    renderer->render();
    film->saveImage("output.png");
}

int main(int argc, char **argv){
    //photonMappingTest();
    //kCaustic();
    //cylinderCaustic(argc, argv);
    //indirectTest(argc, argv);
    //wine(argc, argv);
    //finalRender(argc, argv);
    //texture_CSG_DOF(argc, argv);
    //specular_caustic(argc, argv);
    //globalLighting(argc, argv);
    bump_test(argc, argv);
    //fog(argc, argv);
    //cornell_flood(argc, argv);
    //glass_test();
    //cornell_simple(argc, argv);
    printf("%d %d %d\n", photonGatherTime, photonAddTime, photonGatherTime - photonAddTime);
    return 0;
}
