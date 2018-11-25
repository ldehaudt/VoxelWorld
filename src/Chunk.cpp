#include "stb_image.h"
#include "Chunk.hpp"
#include "Tree.hpp"
#include "Noise.hpp"

void Chunk::SetCurrentRender()
{
	glBindTexture(GL_TEXTURE_2D, texture);
	RenderObject::SetCurrentRender();
}

void Chunk::Render()
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, numVert / 5);
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->SetCurrentRender();
		objects[i]->Render();
	}
}

int Chunk::getTexture(int x, int z)
{
	int tmp = 2;
	if (elev[x][z] + rough[x][z] + 0.4 * local[x][z] > 0.4)
		tmp = 0;
	else if (elev[x][z] + rough[x][z] + 0.2 * local[x][z] > 0.2)
		tmp = 1;
	else if (elev[x][z] + rough[x][z] + 0.1 * local[x][z] < -0.2)
		tmp = 3;
	return (tmp);
}

void	Chunk::placeWall(int x, int z, int y,
	int xOff, int zOff, float blockType, int arr, bool lr, bool cave)
{
	int yGoal;
	if (arr == 0)
		yGoal = heightArr[x - xPos + xOff][z - zPos + zOff];
	if (arr == 4)
		yGoal = heightArr[x - xPos][z - zPos];
	if (arr == 1)
	{
		yGoal = caveButt[x - xPos + xOff][z - zPos + zOff];
		if (yGoal == 0)
		{
			if (caveTop[x - xPos][z - zPos] == 0)
				yGoal = heightArr[x - xPos + xOff][z - zPos + zOff];
			else
				yGoal = caveTop[x - xPos][z - zPos];
		}
	}
	if (arr == 2)
	{
		yGoal = caveTop[x - xPos + xOff][z - zPos + zOff];
		if (yGoal == 0)
			return ;
	}
	int yPos = y;
	while (yPos != yGoal)
	{
		if (yPos > yGoal)
		{
			yPos--;
			if (lr)
				addLR(x + xOff, z + zOff, yPos, 0, blockType);
			else
				addUD(x + xOff, z + zOff, yPos, 0, blockType);
		}
		else
		{
			if (cave)
			{
				if (lr)
					addLR(x + xOff, z + zOff, yPos, 0, blockType);
				else
					addUD(x + xOff, z + zOff, yPos, 0, blockType);
			}
			else
			{
				if (lr)
					addLR(x + xOff, z + zOff, yPos, 0,
					tex[x - xPos + xOff][z - zPos + zOff] / numBlocks);
				else
					addUD(x + xOff, z + zOff, yPos, 0,
					tex[x - xPos + xOff][z - zPos + zOff] / numBlocks);
			}
			yPos++;
		}
	}
}

void	Chunk::addWalls(int x, int z, int y, float blockType, int arr)
{
	if ((caveButt[x - xPos + 1][z - zPos] == 0
	|| caveTop[x - xPos + 1][z - zPos] != 0))
		placeWall(x,z,y, 1, 0, blockType, arr, true, false);
	if ((caveButt[x - xPos][z - zPos + 1] == 0
	|| caveTop[x - xPos][z - zPos + 1] != 0))
		placeWall(x,z,y, 0, 1, blockType, arr, false, false);
}

void	Chunk::addCaveWalls(int x, int z, int y, float blockType, int arr)
{
		placeWall(x,z,y, 1, 0, blockType, arr, true, true);
		placeWall(x,z,y, 0, 1, blockType, arr, false, true);
}

void	Chunk::extraCaveUpWall(int x, int z, int y, float blockType, int arr)
{
		placeWall(x, z, y, 1, 0, blockType, 4, true, true);
		placeWall(x, z, y, 0, 1, blockType, 4, false, true);
		placeWall(x, z, y, 0, 0, blockType, 4, true, true);
		placeWall(x, z, y, 0, 0, blockType, 4, false, true);
}

void	Chunk::extraCaveDownWalls(int x, int z, int y, float blockType)
{
	int yGoal;
	bool skip = false;
	bool t = false;
	yGoal = caveButt[x - xPos - 1][z - zPos];
	if (yGoal == 0)
	{
		if (caveTop[x - xPos][z - zPos] == 0)
		{
			yGoal = heightArr[x - xPos - 1][z - zPos];
			t = true;
		}
		else
			yGoal = caveTop[x - xPos][z - zPos];
	}
	else
		skip = true;
	int yPos = y;
	while (yPos != yGoal && !skip)
	{
		if (yPos > yGoal)
		{
			yPos--;
			addLR(x, z, yPos, 0, blockType);
		}
		else
		{
			if (t)
				addLR(x, z, yPos, 0, tex[x - xPos - 1][z - zPos] / numBlocks);
			else
				addLR(x, z, yPos, 0, blockType);
			yPos++;
		}
	}
	yGoal = caveButt[x - xPos][z - zPos - 1];
	if (yGoal == 0)
	{
		if (caveTop[x - xPos][z - zPos] == 0){
			yGoal = heightArr[x - xPos][z - zPos - 1];
			t = true;
		}
		else{
			yGoal = caveTop[x - xPos][z - zPos];
			t = false;
		}
	}
	else
		return ;
	yPos = y;
	while (yPos != yGoal)
	{
		if (yPos > yGoal)
		{
			yPos--;
			addUD(x, z, yPos, 0, blockType);
		}
		else
		{
			if (t)
				addUD(x, z, yPos, 0, tex[x - xPos][z - zPos - 1] / numBlocks);
			else
				addUD(x, z, yPos, 0, blockType);
			yPos++;
		}
    }
}

void	Chunk::LoadChunk()
{
	for (int x = 0; x < 18; x++){
		for (int z = 0; z < 18; z++){
			float px = (xPos + x - 1) / 16.0;
			float pz = (zPos + z - 1) / 16.0;
			rough[x][z] = Noise::singleton->roughness(px / 47, pz / 47);
			elev[x][z] = Noise::singleton->elevation(px / 11, pz / 11);
			local[x][z] = Noise::singleton->local(px / 1.8, pz / 1.8);
			float h = rough[x][z] + elev[x][z];
			if (h > 0)
				h *= (1 + 0.5 * local[x][z]);
			int t = int(h * 128 + 100);
			if (t < 1 || t > 255)
				heightArr[x][z] = (t < 1 ? 1 : 255);
			else
				heightArr[x][z] = t;
			tex[x][z] = getTexture(x, z);
			if (h > 0.21 && h < 0.27)
			{
				int c = int((0.7 - local[x][z]) * 25 + 110);
				int r = int((1 - (abs(h - 0.24) * 33))
					* max(4, (heightArr[x][z] - c) / 2));
				if (r >= 0)
				{
					if (c - r < heightArr[x][z])
						caveButt[x][z] = c - r;
					if (c + r < heightArr[x][z])
						caveTop[x][z] = c + r;
				}
			}
		}
	}
}

Chunk::Chunk(Shader& sha, Camera& c, float xIn, float zIn, char *grass)
	: RenderObject(sha, c, xPos, 0, zPos, 1, 1, 1)
{
	verts = (float*)calloc(1000000, sizeof(float));
	xPos = xIn;
	zPos = zIn;
	int totalH = 0;
	bool cave = false;
	numVert = 0;
	numInd = 0;

	LoadChunk();
	for (int x = 1; x < 17; x++)
	{
		for (int z = 1; z < 17; z++)
		{
			if (caveButt[x][z] == 0 || caveTop[x][z] != 0)
			{
				addFlat(xPos + x, zPos + z, heightArr[x][z], 1 / 3.0, tex[x][z] / numBlocks);
				addWalls(xPos + x, zPos + z, heightArr[x][z], tex[x][z] / numBlocks, 0);
			}
			if (caveTop[x][z] != 0)
			{
				addFlat(xPos + x, zPos + z, caveTop[x][z], 0.0, 4.0 / numBlocks);
				addCaveWalls(xPos + x, zPos + z, caveTop[x][z], 1.0 / numBlocks, 2);
				extraCaveUpWall(xPos + x, zPos + z, caveTop[x][z], 1.0 / numBlocks, 2);
			}
			if (caveButt[x][z] != 0)
			{
				addFlat(xPos + x, zPos + z, caveButt[x][z], 1 / 3.0, 4.0 / numBlocks);
				addCaveWalls(xPos + x, zPos + z, caveButt[x][z], 1.0 / numBlocks , 1);
				extraCaveDownWalls(xPos + x, zPos + z, caveButt[x][z], 1.0 / numBlocks);
			}
			addObjects(x, z);
		}
	}
	unsigned char *data = stbi_load(grass, &width, &height, &nrChannels, 0);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	Activate();
}

void	Chunk::addObjects(int x, int z)
{
	float h = elev[x][z] + rough[x][z];
	if (tex[x][z] == 2 && elev[x][z] > -0.1 && elev[x][z] < 0.2)
	{
		h = pow(abs((h - 0.05) / 0.25), 3);
		if (Noise::singleton->detailRand[((x + xPos) * 103) & 63][((z + zPos)  * 97) & 63]
		 * (1 - abs(elev[x][z] - 0.05) / 0.15) < h * 0.001)
		{
			objects.push_back(new Tree(shader, cam, x + xPos,
			heightArr[x][z], z + zPos, "textures/Tree.png"));
		}
	}
}

void	Chunk::Activate()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVert, verts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),(void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

Chunk::~Chunk(){
	glDeleteTextures(1, &texture);

	for (int i = 0; i < objects.size(); i++)
		delete(objects[i]);
	objects.clear();
}
