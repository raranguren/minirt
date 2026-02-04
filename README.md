# miniRT

A minimal raytracer built in C as part of the 42 school curriculum

<img width="526" height="398" alt="image" src="https://github.com/user-attachments/assets/26e311c5-7824-4424-a710-e0a12eaa7ea9" />


## Overview

miniRT renders 3D scenes defined in `.rt` files using raytracing techniques. The project implements basic geometric primitives, Phong lighting, and an interactive scene editor.

## Features

**Mandatory**
- Geometric primitives: spheres, planes, cylinders
- Ambient and point lighting
- Camera with configurable FOV

**Bonus**
- Cones
- Full Phong reflection model with specular highlights
- Bump mapping via XPM textures
- Checkerboard patterns
- Multiple colored light sources

**We wanted it**
- Real-time scene editing with GUI, keys and mouse

## Building

```bash
make        # Build mandatory version
make bonus  # Build bonus version
```

## Usage

```bash
./miniRT scenes/example.rt
./miniRT_bonus scenes/example.rt
./miniRT -h   # Display help
```

or simply
```bash
make demo
make demo_bonus
```
(see below the screenshots from the demo scenes)

## Scene Format

Scenes are defined in `.rt` files with the following elements:

| Element | Syntax |
|---------|--------|
| Ambient | `A <ratio> <r,g,b>` |
| Camera | `C <x,y,z> <dir_x,dir_y,dir_z> <fov>` |
| Light | `L <x,y,z> <ratio> <r,g,b>` |
| Sphere | `sp <x,y,z> <diameter> <r,g,b>` |
| Plane | `pl <x,y,z> <normal_x,y,z> <r,g,b>` |
| Cylinder | `cy <x,y,z> <axis_x,y,z> <diameter> <height> <r,g,b>` |
| Cone | `co <x,y,z> <axis_x,y,z> <diameter> <height> <r,g,b>` *(bonus)* |

## Controls

| Key | Action |
|-----|--------|
| `N` / `P` | Select next/previous object |
| `I/J/K/L` | Move object (forward/left/back/right) |
| `U/H` | Move object (up/down) |
| `↑/↓/←/→` | Rotate object |
| `V/B` | Decrease/increase radius |
| `X/C` | Decrease/increase height |
| `0-9` | Quick color presets |
| `Space` | Snap to grid |
| `Left click` | Select object |
| `Right click` | Point camera |
| `Esc` | Exit (saves to `snapshot.rt`) |

## Dependencies

- MiniLibX (cloned automatically)
- X11 development libraries

```bash
# Debian/Ubuntu
sudo apt install libx11-dev libxext-dev
```

## Authors

- **bduval** — [Github profile](https://github.com/1Batmain)
- **rarangur** — [Github profile](https://github.com/raranguren)

---

*42 School Project — 2025*

## Examples

Colored spheres, cylinders and planes. Shadow casting from a single spot light.

<img width="1082" height="759" alt="image" src="https://github.com/user-attachments/assets/0e4c47f8-e1f4-46bd-ad85-2a3ee53177fd" />
<img width="1082" height="759" alt="image" src="https://github.com/user-attachments/assets/f71add82-740b-421d-905d-2fa28de99ee8" />
<img width="1082" height="759" alt="image" src="https://github.com/user-attachments/assets/19284d95-be97-4412-acc0-00dd602bff36" />

The interior of shapes is also calculated. This is the camera and the light inside a cylinder that is inside a blue sphere, with yellow spheres as decoration.

<img width="1082" height="759" alt="image" src="https://github.com/user-attachments/assets/23a68a97-1c65-4a3b-be21-673159cae851" />

The same three simple shapes aligned to form interesting artistic compositions.

<img width="1082" height="759" alt="image" src="https://github.com/user-attachments/assets/e82b8236-036f-4483-b383-f17d9152891b" />
<img width="1082" height="759" alt="image" src="https://github.com/user-attachments/assets/736343e2-d72f-475d-9347-8f7832cc470a" />

### Colored lights and phong reflections

A blue light illuminating a white cylinder and a red sphere. The sphere appears totally dark.
<img width="1082" height="759" alt="image" src="https://github.com/user-attachments/assets/291cb2ed-6f03-4b14-9247-dae0b30f77b2" />

Phong reflections are correctly calculated; note how 3 lights reflect on the cylinder but only 2 on the sphere.
<img width="1082" height="759" alt="image" src="https://github.com/user-attachments/assets/e33a24d3-a9ba-44f9-ba5b-89b382e23244" />

These 5 light sources reflect off the plane and the base of the cylinder, creating an interesting shadow gradient.
<img width="1082" height="759" alt="image" src="https://github.com/user-attachments/assets/8ba68fcd-b7ce-4f1f-aa87-83a9694c806d" />

This demonstrates how light composition works naturally, with blue, green, and red lights creating white, magenta, cyan, and yellow.
<img width="1082" height="759" alt="image" src="https://github.com/user-attachments/assets/3ee0d204-eed0-41ba-ad45-21f8f6368427" />

### Extra shape: cone

<img width="1082" height="759" alt="image" src="https://github.com/user-attachments/assets/b357f0bb-9112-4620-be7e-bb11ee54698e" />
<img width="1082" height="759" alt="image" src="https://github.com/user-attachments/assets/24da4075-3ffd-41be-b400-cbd080af1691" />

### Color disruption: checkered pattern on spheres

<img width="1082" height="759" alt="image" src="https://github.com/user-attachments/assets/c7501bb1-de7c-4c8f-8c0f-cbb73d6a5105" />

### Bump maps

A white sphere with a yellow light on top and a blue light below, with a bump map of the continents of the Earth.
<img width="1082" height="759" alt="image" src="https://github.com/user-attachments/assets/988952d8-cd2b-40db-bb68-fd61caccc118" />

Bump maps and phong effects work correctly with multiple spot lights.
<img width="1082" height="759" alt="image" src="https://github.com/user-attachments/assets/8544a75c-0624-4112-adfe-548d457235b9" />

Bump maps can also be applied to cones.
<img width="1082" height="759" alt="image" src="https://github.com/user-attachments/assets/2f5a1de9-d9b4-4323-bb47-949d002fd802" />



