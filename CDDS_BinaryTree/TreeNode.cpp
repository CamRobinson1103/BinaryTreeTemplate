#include "TreeNode.h"
#include <iostream>
#include "raylib.h"

TreeNode::TreeNode(int value)
{
	m_value = value;
}

void TreeNode::draw(int x, int y, bool selected)
{
	//Creates an array to store the value converted to a string
	static char buffer[12];

	sprintf(buffer, "%d", m_value);

	// Draw the node to the screen
	DrawCircle(x, y, 30, YELLOW);

	
	if (selected)
		DrawCircle(x, y, 28, GREEN);
	else
		DrawCircle(x, y, 28, BLACK);

	// Draw value over the node
	DrawText(buffer, x - 12, y - 12, 12, WHITE);
}