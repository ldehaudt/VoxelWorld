#include "ChunkManager.hpp"
#import <thread> 

ChunkManager* ChunkManager::singleton = NULL;

ChunkManager::ChunkManager(Shader &s, Camera &c, int playerX, int playerZ)
: shader(s), cam(c)
{
	if (ChunkManager::singleton != NULL)
		return;

	curX = playerX / 16;
	curZ = playerZ / 16;
	chunks.reserve(chunkRad * 2 + 1);
	for (int z = curZ + chunkRad; z >= curZ - chunkRad; z--){
		std::vector<Chunk*> vec;
		chunks.push_back(vec);
		chunks[chunks.size() - 1].reserve(chunkRad * 2 + 1);
		for (int x = curX - chunkRad; x <= curX + chunkRad; x++){
			Chunk * ch = new Chunk(shader, cam, x * 16, z * 16, "textures/blocks.png");
			chunks[chunks.size() - 1].push_back(ch);
		}
	}
	ChunkManager::singleton = this;
}

ChunkManager::~ChunkManager()
{
	for (int z = 0; z <= chunkRad * 2; z++)
		for (int x = 0; x <= chunkRad * 2; x++)
			delete(chunks[x][z]);
}

void	ChunkManager::renderChunks()
{
	int num = 0;
	for (int x = 0 ; x <= chunkRad * 2; x++){
		for (int z = 0 ; z <= chunkRad * 2; z++)
		{
			num++;
			chunks[z][x]->SetCurrentRender();
			chunks[z][x]->Render();
		}
	}
}

Chunk	&ChunkManager::getPlayerChunk(){
	return *(chunks[chunkRad][chunkRad]);
}

void	ChunkManager::loadHoriz(int pos)
{
	for (int i = -chunkRad; i <= chunkRad; i++)
	{
		if (pos > curX)
		{
			Chunk * tmp = chunks[i + chunkRad][0];
			chunks[i + chunkRad].erase(chunks[i + chunkRad].begin());
			chunks[i + chunkRad].push_back(new Chunk(shader, cam, pos * 16,
				(-i +  curZ) * 16, "textures/blocks.png"));
			delete(tmp);
		}
		else
		{
			Chunk * tmp = chunks[i + chunkRad][chunks.size() - 1]; 
			chunks[i + chunkRad].erase(chunks[i + chunkRad].end() - 1);
			chunks[i + chunkRad].insert(chunks[i + chunkRad].begin(),
				new Chunk(shader, cam, pos * 16, (-i + curZ) * 16, "textures/blocks.png"));
			delete(tmp);
		}
	}
}

void	ChunkManager::loadVert(int pos)
{
	std::vector<Chunk*> vec;
	for (int i = -chunkRad; i <= chunkRad; i++)
		vec.push_back(new Chunk(shader, cam, (curX + i) * 16, pos * 16, "textures/blocks.png"));
	if (pos > curZ)
	{
		for (int i = 0; i <= chunkRad * 2; i++){
			delete(chunks[chunks.size() - 1][i]);
		}
		chunks.erase(chunks.end() - 1);
		chunks.insert(chunks.begin(), vec);
	}
	else
	{
		for (int i = 0; i <= chunkRad * 2; i++){
			delete(chunks[0][i]);
		}
		chunks.erase(chunks.begin());
		chunks.push_back(vec);		
	}
}

void	ChunkManager::PlayerMoved(int xPos, int zPos)
{
	int newX = xPos / 16;
	int newZ = zPos / 16;
	
	if (newX != curX)
	{
		if (newX > curX)
		{
			curX++;
			loadHoriz(curX + chunkRad);
		}
		else
		{
			curX--;
			loadHoriz(curX - chunkRad);	
		}
	}
	if (newZ != curZ)
	{
		if (newZ > curZ)
		{
			curZ++;
			loadVert(curZ + chunkRad);
		}
		else{
			curZ--;
			loadVert(curZ - chunkRad);	
		}
	}
}
