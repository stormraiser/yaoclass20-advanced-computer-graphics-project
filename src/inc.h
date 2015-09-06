#pragma once

#include "Core/Scene.h"
#include "Core/Film.h"

#include "Primitives/Cuboid.h"
#include "Primitives/Sphere.h"
#include "Primitives/Cylinder.h"

#include "Primitives/MeshObject.h"

#include "Core/CSGObject.h"

#include "Lights/PointLight.h"
#include "Lights/SpotLight.h"
#include "Lights/SquareLight.h"

#include "Lights/EnviromentLight.h"

#include "Cameras/BasicCameras.h"
#include "Cameras/Fisheyes.h"
#include "Cameras/Panoramics.h"

#include "BSDFs/SpecularBSDF.h"
#include "BSDFs/PhongBSDF.h"
#include "BSDFs/LambertianBSDF.h"
#include "BSDFs/PhaseIsotropic.h"
#include "BSDFs/FresnelBSDF.h"
#include "BSDFs/FresnelBlendBSDF.h"
#include "BSDFs/MappingBlendedBSDF.h"

#include "Mappings/PureColor.h"
#include "Mappings/CheckerColor.h"
#include "Mappings/CheckerTexture.h"
#include "Mappings/BitmapTexture.h"
#include "Mappings/BitmapMapping.h"
#include "Mappings/PerlinNoise3D.h"
#include "Mappings/BitmapBumpMapping.h"

#include "Renderers/MonteCarloPathTracer.h"
#include "Renderers/PhotonMappingRenderer.h"
