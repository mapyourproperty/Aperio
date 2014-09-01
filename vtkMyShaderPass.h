///*=========================================================================
//
//  Program:   Visualization Toolkit
//  Module:    vtkMyShaderPass.h
//
//  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
//  All rights reserved.
//  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.
//
//     This software is distributed WITHOUT ANY WARRANTY; without even
//     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//     PURPOSE.  See the above copyright notice for more information.
//
//=========================================================================*/
// .NAME vtkMyShaderPass - Render the opaque/translucent geometry with property key
// filtering.
// .SECTION Description
// vtkMyShaderPass renders the opaque/translucent geometry of all the props that have the
// keys contained in vtkRenderState.
//
// This pass expects an initialized depth buffer and color buffer.
// Initialized buffers means they have been cleared with farest z-value and
// background color/gradient/transparent color.
//
// .SECTION See Also
// vtkRenderPass vtkDefaultPass

#ifndef __vtkMyShaderPass_h
#define __vtkMyShaderPass_h

#include <vtkRenderingOpenGLModule.h> // For export macro
#include <vtkDefaultPass.h>
#include "vtkInformationIntegerKey.h"

class aperio;	// pimpl

// Enumeration for RenderPass Type (opaque, translucency)
struct ShaderPassType
{
	static enum T { PASS_OPAQUE, PASS_TRANSLUCENT };
};

class VTK_EXPORT vtkMyShaderPass : public vtkDefaultPass
{
public:
	static vtkMyShaderPass *New();
	vtkTypeMacro(vtkMyShaderPass, vtkDefaultPass);
	void PrintSelf(ostream& os, vtkIndent indent);

	// --- Custom Property Keys
	static vtkInformationIntegerKey *OUTLINEKEY();

	//BTX
	// Description:
	// Perform rendering according to a render state \p s.
	// \pre s_exists: s!=0
	virtual void Render(const vtkRenderState *s);

	// My Custom methods
	virtual void RenderGeometry(const vtkRenderState *s);	// modified RenderFilteredOpaqueGeometry from vtkDefaultPass

	//vtkGetMacro(translucentPass, bool);
	//vtkSetMacro(translucentPass, bool);

	// The main variables initializer since constructors are not used (initializes aperio class reference & PassType)
	// MUST be called first before running
	void initialize(aperio * window, ShaderPassType::T passType);

	// My Custom variables
	aperio *a;
	vtkSmartPointer<vtkUniformVariables> uniforms;
	ShaderPassType::T passType;

	//ETX

protected:
	// Description:
	// Default constructor.
	vtkMyShaderPass();

	// Description:
	// Destructor.
	virtual ~vtkMyShaderPass();

private:
	vtkMyShaderPass(const vtkMyShaderPass&);  // Not implemented.
	void operator=(const vtkMyShaderPass&);  // Not implemented.
};
#endif