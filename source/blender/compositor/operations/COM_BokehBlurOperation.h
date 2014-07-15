/*
 * Copyright 2011, Blender Foundation.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * Contributor: 
 *		Jeroen Bakker 
 *		Monique Dewanchand
 */

#ifndef __COM_BOKEHBLUROPERATION_H__
#define __COM_BOKEHBLUROPERATION_H__

#include "COM_NodeOperation.h"
#include "COM_QualityStepHelper.h"
#include "COM_Sampler.h"

class BokehBlurOperation : public NodeOperation, public QualityStepHelper {
private:
	SocketReader *m_inputProgram;
	SocketReader *m_inputBokehProgram;
	SocketReader *m_inputBoundingBoxReader;
	SamplerNearestColor *m_bokeh_sampler;
	SamplerNearestValue *m_boundingbox_sampler;

	void updateSize();
	float m_size;
	bool m_sizeavailable;
	float m_bokehMidX;
	float m_bokehMidY;
	float m_bokehDimension;
public:
	BokehBlurOperation();

	void *initializeTileData(rcti *rect);
	/**
	 * the inner loop of this program
	 */
	void executePixel(float output[4], int x, int y, void *data);
	
	/**
	 * Initialize the execution
	 */
	void initExecution();
	
	/**
	 * Deinitialize the execution
	 */
	void deinitExecution();
	
	bool determineDependingAreaOfInterest(rcti *input, ReadBufferOperation *readOperation, rcti *output);

	void setSize(float size) { this->m_size = size; this->m_sizeavailable = true; }
	
	void executeOpenCL(OpenCLDevice *device,
	                   MemoryBuffer *outputMemoryBuffer, cl_mem clOutputBuffer,
	                   MemoryBuffer **inputMemoryBuffers, list<cl_mem> *clMemToCleanUp,
	                   list<cl_kernel> *clKernelsToCleanUp);
};
#endif
