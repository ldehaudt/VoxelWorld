#ifndef CHUNKMANAGER_HPP
#define CHUNKMANAGER_HPP

#include "graphics.hpp"
#include "Chunk.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include <vector>

class ChunkManager{
	public:
		ChunkManager(Shader &s, Camera &c, int, int);
		~ChunkManager();

		vector< vector<Chunk*> > chunks;

		static ChunkManager* singleton;
		void	loadVert(int pos);
		void	loadHoriz(int pos);
		void	renderChunks();

		void	multiHoriz(int pos, int st, int end);
		void	PlayerMoved(int xPos, int zPos);
		Chunk	&getPlayerChunk();

		Shader &shader;
		Camera &cam;
		int chunkRad = 10;
		int curX;
		int curZ;
};

#endif