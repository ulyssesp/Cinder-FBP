#include "ProcessNode.h"

#include "cinder/app/App.h"

ProcessNode::ProcessNode(std::string name, std::vector<std::string> inputIds) : mLastFrame(-1), mName(name), mInputIds(inputIds) {}

void ProcessNode::setData(std::string id, boost::any data)
{
	mData[id] = data;
}

boost::any ProcessNode::getInputData(std::string id, int frame)
{
	if (mInputs.find(id) == mInputs.end()) {
		return boost::any();
	}

	FBPInputNode in = mInputs[id];

	return in.node->getData(in.id, frame);
}

boost::any ProcessNode::getInputData(std::string id)
{
	if (mInputs.find(id) == mInputs.end()) {
		return boost::any();
	}

	FBPInputNode in = mInputs[id];

	return in.node->getData(in.id);
}

float ProcessNode::getInputDataAsFloat(std::string id, float default, int frame)
{
	boost::any data = getInputData(id, frame);

	if (data.empty()) {
		return default;
	}

	float out;
	try {
		out = boost::any_cast<float>(data);
	}
	catch (boost::bad_any_cast e) {
		out = std::stof(boost::any_cast<std::string>(data));
	}

	return out;
}

void ProcessNode::setInput(std::string id, FBPInputNode FBPInputNode) 
{
	if (std::find(mInputIds.begin(), mInputIds.end(), id) == mInputIds.end()) {
		ci::app::console() << "You tried to set input " << id << " on " << mName << " where there isn't such an input.";
		throw;
	}

	mInputs[id] = FBPInputNode;
}

boost::any ProcessNode::getData(std::string id, int frame)
{
	if (frame > mLastFrame) {
		update(frame);
		mLastFrame = frame;
	}

	if (mData.find(id) == mData.end()) {
		return boost::any();
	}

	return mData[id];
}

boost::any ProcessNode::getData(std::string id)
{
	if (mData.find(id) == mData.end()) {
		return boost::any();
	}

	return mData[id];
}
