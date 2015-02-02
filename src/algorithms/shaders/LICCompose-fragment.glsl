//---------------------------------------------------------------------------------------
//
// Project: DirectionalityIndicator
//
// Copyright 2014-2015 Sebastian Eichelbaum (http://www.sebastian-eichelbaum.de)
//           2014-2015 Max Planck Research Group "Neuroanatomy and Connectivity"
//
// This file is part of DirectionalityIndicator.
//
// DirectionalityIndicator is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// DirectionalityIndicator is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with DirectionalityIndicator. If not, see <http://www.gnu.org/licenses/>.
//
//---------------------------------------------------------------------------------------

#version 330

// Uniforms
uniform sampler2D u_colorSampler;
uniform sampler2D u_vecSampler;
uniform sampler2D u_depthSampler;
uniform sampler2D u_edgeSampler;
uniform sampler2D u_noiseSampler;
uniform sampler2D u_advectSampler;

// Varyings
in vec2 v_texCoord;

// Outputs
out vec4 fragColor;

void main()
{
    vec4 color = texture( u_colorSampler,  v_texCoord ).rgba;
    vec3 vec = texture( u_vecSampler, v_texCoord ).rgb;
    float depth = texture( u_depthSampler, v_texCoord ).r;
    float edge = texture( u_edgeSampler, v_texCoord ).r;
    float noise = texture( u_noiseSampler, v_texCoord ).r;
    vec3 advect = texture( u_advectSampler, v_texCoord ).rgb;

    vec4 col = vec4(
        mix(
            mix( color.rgb, vec3( 1.0 ), 1.0 * edge ),
            advect, 0.5 ),
        color.a
    );

    fragColor = col;
    gl_FragDepth = depth;
}

