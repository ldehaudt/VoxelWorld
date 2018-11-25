#include "Chunk.hpp"

void    Chunk::addFlat(int x, int z, int y, float startX, float startY)
{
	verts[numVert++] = x;
	verts[numVert++] = y;
	verts[numVert++] = z;
	verts[numVert++] = startX;
	verts[numVert++] = startY;
	verts[numVert++] = x;
	verts[numVert++] = y;
	verts[numVert++] = z + 1;
	verts[numVert++] = startX;
	verts[numVert++] = startY + 1.0 / numBlocks;
	verts[numVert++] = x + 1;
	verts[numVert++] = y;
	verts[numVert++] = z;
	verts[numVert++] = startX + 1.0/3.0;
	verts[numVert++] = startY;
	verts[numVert++] = x + 1;
	verts[numVert++] = y;
	verts[numVert++] = z + 1;
	verts[numVert++] = startX + 1.0/3.0;
	verts[numVert++] = startY + 1.0 / numBlocks;
	verts[numVert++] = x + 1;
	verts[numVert++] = y;
	verts[numVert++] = z;
	verts[numVert++] = startX + 1.0/3.0;
	verts[numVert++] = startY;
	verts[numVert++] = x;
	verts[numVert++] = y;
	verts[numVert++] = z + 1;
	verts[numVert++] = startX;
	verts[numVert++] = startY + 1.0 / numBlocks;
}

void    Chunk::addLR(int x, int z, int y, float startX, float startY)
{
	verts[numVert++] = x;
	verts[numVert++] = y;
	verts[numVert++] = z;
	verts[numVert++] = startX;
	verts[numVert++] = startY + 1.0 / numBlocks;
	verts[numVert++] = x;
	verts[numVert++] = y + 1;
	verts[numVert++] = z;
	verts[numVert++] = startX;
	verts[numVert++] = startY;
	verts[numVert++] = x;
	verts[numVert++] = y;
	verts[numVert++] = z + 1;
	verts[numVert++] = startX + 1.0/3.0;
	verts[numVert++] = startY + 1.0 / numBlocks;
	verts[numVert++] = x;
	verts[numVert++] = y + 1;
	verts[numVert++] = z + 1;
	verts[numVert++] = startX + 1.0/3.0;
	verts[numVert++] = startY;
	verts[numVert++] = x;
	verts[numVert++] = y + 1;
	verts[numVert++] = z;
	verts[numVert++] = startX;
	verts[numVert++] = startY;
	verts[numVert++] = x;
	verts[numVert++] = y;
	verts[numVert++] = z + 1;
	verts[numVert++] = startX + 1.0 / 3.0;
	verts[numVert++] = startY + 1.0 / numBlocks;
}

void    Chunk::addUD(int x, int z, int y, float startX, float startY)
{
	verts[numVert++] = x;
	verts[numVert++] = y;
	verts[numVert++] = z;
	verts[numVert++] = startX;
	verts[numVert++] = startY + 1.0 / numBlocks;
	verts[numVert++] = x;
	verts[numVert++] = y + 1;
	verts[numVert++] = z;
	verts[numVert++] = startX;
	verts[numVert++] = startY;
	verts[numVert++] = x + 1;
	verts[numVert++] = y;
	verts[numVert++] = z;
	verts[numVert++] = startX + 1.0/3.0;
	verts[numVert++] = startY + 1.0 / numBlocks;
	verts[numVert++] = x + 1;
	verts[numVert++] = y + 1;
	verts[numVert++] = z;
	verts[numVert++] = startX + 1.0/3.0;
	verts[numVert++] = startY;
	verts[numVert++] = x;
	verts[numVert++] = y + 1;
	verts[numVert++] = z;
	verts[numVert++] = startX;
	verts[numVert++] = startY;
	verts[numVert++] = x + 1;
	verts[numVert++] = y;
	verts[numVert++] = z;
	verts[numVert++] = startX + 1.0/3.0;
	verts[numVert++] = startY + 1.0 / numBlocks;
}
