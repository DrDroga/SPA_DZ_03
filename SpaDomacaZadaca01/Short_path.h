#pragma once
#include<vector>
#include<list>
#include <iostream>
using namespace std;

class Short_path
{

	public:
		Short_path()
		{
			OnUserCreate();
		}
		void setStart(int x, int y)
		{
			nodeStart = &nodes[y * nMapWidth + x];
		}
		void setEnd(int x, int y) {
			nodeEnd = &nodes[y * nMapWidth + x];
		}
		void setObstacle(int x, int y) {
			nodes[y * nMapWidth + x].bObstacle = true;
		}
		void unsetObstacle(int x, int y) {
			nodes[y * nMapWidth + x].bObstacle = false;
		}

		bool getVisitedState(int x, int y) {
			if (nodes[y * nMapWidth + x].bVisited == true)
				return 1;
			else
				return 0;
		}
		bool getParentState(int x, int y)
		{
			path();
			if (nodes[y * nMapWidth + x].isParent == true)
				return 1;
			else
				return 0;

		}

	private:
		struct sNode
		{
			bool isParent = false;
			bool bObstacle = false;
			bool bVisited = false;
			float fGlobalGoal;
			float fLocalGoal;
			int x;
			int y;
			vector<sNode*> vecNeighbours;
			sNode* parent;

		};

		sNode* nodes = nullptr;
		int nMapWidth = 40;
		int nMapHeight = 40;

		sNode* nodeStart = nullptr;
		sNode* nodeEnd = nullptr;


	protected:


		void OnUserCreate()
		{
			nodes = new sNode[nMapWidth * nMapHeight];
			for (int x = 0; x < nMapWidth; x++)
				for (int y = 0; y < nMapHeight; y++)
				{
					nodes[y * nMapWidth + x].x = x;
					nodes[y * nMapWidth + x].y = y;
					nodes[y * nMapWidth + x].bObstacle = false;
					nodes[y * nMapWidth + x].parent = nullptr;
					nodes[y * nMapWidth + x].bVisited = false;

				}

			for (int x = 0; x < nMapWidth; x++)
				for (int y = 0; y < nMapHeight; y++)
				{
					if (y > 0)
						nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * nMapWidth + (x + 0)]);
					if (y < nMapHeight - 1)
						nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * nMapWidth + (x + 0)]);
					if (x > 0)
						nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 0) * nMapWidth + (x - 1)]);
					if (x < nMapWidth - 1)
						nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 0) * nMapWidth + (x + 1)]);

				}


			nodeStart = &nodes[0];
			nodeEnd = &nodes[9 * 40 + 9 - 1];

		}
	public:
		void Solve_Short_path()
		{

			for (int x = 0; x < nMapWidth; x++)
				for (int y = 0; y < nMapHeight; y++)
				{
					nodes[y * nMapWidth + x].isParent = false;
					nodes[y * nMapWidth + x].bVisited = false;
					nodes[y * nMapWidth + x].fGlobalGoal = INFINITY;
					nodes[y * nMapWidth + x].fLocalGoal = INFINITY;
					nodes[y * nMapWidth + x].parent = nullptr;
				}

			auto distance = [](sNode* a, sNode* b)
			{
				return sqrtf((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
			};

			auto heuristic = [distance](sNode* a, sNode* b)
			{
				return distance(a, b);
			};

			sNode* nodeCurrent = nodeStart;
			nodeStart->fLocalGoal = 0.0f;
			nodeStart->fGlobalGoal = heuristic(nodeStart, nodeEnd);

			list<sNode*> listNotTestedNodes;
			listNotTestedNodes.push_back(nodeStart);

			while (!listNotTestedNodes.empty() && nodeCurrent != nodeEnd)
			{

				listNotTestedNodes.sort([](const sNode* lhs, const sNode* rhs) 
					{ return lhs->fGlobalGoal < rhs->fGlobalGoal; });

				while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->bVisited)
					listNotTestedNodes.pop_front();

				if (listNotTestedNodes.empty())
					break;

				nodeCurrent = listNotTestedNodes.front();
				nodeCurrent->bVisited = true;

				for (auto nodeNeighbour : nodeCurrent->vecNeighbours)
				{
					if (!nodeNeighbour->bVisited && nodeNeighbour->bObstacle == 0)
						listNotTestedNodes.push_back(nodeNeighbour);

					float fPossiblyLowerGoal = nodeCurrent->fLocalGoal + distance(nodeCurrent, nodeNeighbour);

					if (fPossiblyLowerGoal < nodeNeighbour->fLocalGoal)
					{
						nodeNeighbour->parent = nodeCurrent;
						nodeNeighbour->fLocalGoal = fPossiblyLowerGoal;

						nodeNeighbour->fGlobalGoal = nodeNeighbour->fLocalGoal + heuristic(nodeNeighbour, nodeEnd);
					}
				}
			}
		}
		void path() {

			if (nodeEnd != nullptr)
			{
				sNode* p = nodeEnd;
				while (p->parent != nullptr)
				{

					nodes[p->y * nMapWidth + p->x].isParent = true;
					p = p->parent;
				}
			}
		}

		

			

	


};

