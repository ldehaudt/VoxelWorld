#ifndef CHUNK_HPP
#define CHUNK_HPP
#include "RenderObject.hpp"
#include <vector>

class Chunk : public RenderObject{
    public:
        Chunk(Shader& sha, Camera & c, float x, float z, char *);
        ~Chunk();
        void    Activate();
        void    SetCurrentRender();
        void addObjects(int x, int y);
        vector<RenderObject*> objects;
        void    Render();
        void    LoadChunk();
        void    extraCaveUpWall(int x, int z, int y, float blockType, int arr);
        void    placeWall(int x, int z, int y,
            int xOff, int zOff, float blockType, int arr, bool, bool);
        void    addWalls(int x, int z, int y, float blockType, int);
        void    addCaveWalls(int x, int z, int y, float blockType, int);
        void    extraCaveDownWalls(int x, int z, int y, float blockType);
        void    addFlat(int x, int z, int y, float, float);
        void    addUD(int x, int z, int y, float, float);
        void    addLR(int x, int z, int y, float, float);
        int     getTexture(int x, int z);
        int xPos,zPos;
        unsigned char heightArr[18][18];
        unsigned char caveButt[18][18] = {0};
        unsigned char caveTop[18][18] = {0};
        float elev[18][18];
        float rough[18][18];
        float local[18][18];
        unsigned char tex[18][18];
        const float numBlocks = 5;
        int             width, height, nrChannels;
        unsigned int    texture;
};

#endif
