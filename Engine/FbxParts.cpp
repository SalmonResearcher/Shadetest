#include "FbxParts.h"
#include "Fbx.h"
#include "Direct3D.h"
#include "Camera.h"

FbxParts::FbxParts()
{}

FbxParts::~FbxParts()
{
	SAFE_DELETE(pBoneArray_);
	SAFE_DELETE(ppCluster_);

	if (pWeightArray_ != nullptr)
	{
		for (DWORD i = 0; i < vertexCount_; i++)
		{
			SAFE_DELETE(pWeightArray_[i].pBoneIndex);
			SAFE_DELETE_ARRAY(pWeightArray_[i].pBoneWeight);
		}
		SAFE_DELETE_ARRAY(pWeightArray_);
}