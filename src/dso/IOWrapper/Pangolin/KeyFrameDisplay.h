/**
* This file is part of DSO, written by Jakob Engel.
* It has been modified by Lukas von Stumberg for the inclusion in DM-VIO (http://vision.in.tum.de/dm-vio).
*
* Copyright 2022 Lukas von Stumberg <lukas dot stumberg at tum dot de>
* Copyright 2016 Technical University of Munich and Intel.
* Developed by Jakob Engel <engelj at in dot tum dot de>,
* for more information see <http://vision.in.tum.de/dso>.
* If you use this code, please cite the respective publications as
* listed on the above website.
*
* DSO is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* DSO is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with DSO. If not, see <http://www.gnu.org/licenses/>.
*/


#pragma once

#undef Success
#include <Eigen/Core>
#include "util/NumType.h"
#include <pangolin/pangolin.h>

#include <sstream>
#include <fstream>

namespace dso
{
class CalibHessian;
class FrameHessian;
class FrameShell;

namespace IOWrap
{

template<int ppp>
struct InputPointSparse
{
	float u;
	float v;
	float idpeth;
	float idepth_hessian;
	float relObsBaseline;
	int numGoodRes;
	unsigned char color[ppp];
	unsigned char status;

	int object_status = 0;
};

struct MyVertex
{
	float point[3];
	unsigned char color[4];
};

// stores a pointcloud associated to a Keyframe.
class KeyFrameDisplay
{

public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
	KeyFrameDisplay();
	~KeyFrameDisplay();

	// copies points from KF over to internal buffer,
	// keeping some additional information so we can render it differently.
	void setFromKF(FrameHessian* fh, CalibHessian* HCalib);

	// copies points from KF over to internal buffer,
	// keeping some additional information so we can render it differently.
	void setFromF(FrameShell* fs, CalibHessian* HCalib);

	void setFromPose(const Sophus::SE3& pose, CalibHessian* HCalib);

	// copies & filters internal data to GL buffer for rendering. if nothing to do: does nothing.
	bool refreshPC(bool canRefresh, float scaledTH, float absTH, int mode, float minBS, int sparsity);

	// renders cam & pointcloud.
	void drawCam(float lineWidth = 1, float* color = 0, float sizeFactor=1);
	void drawPC(float pointSize);

	int id;
	bool active;
	SE3 camToWorld;

    inline bool operator < (const KeyFrameDisplay& other) const
    {
        return (id < other.id);
    }


private:
	float fx,fy,cx,cy;
	float fxi,fyi,cxi,cyi;
	int width, height;

	float my_scaledTH, my_absTH, my_scale;
	int my_sparsifyFactor;
	int my_displayMode;
	float my_minRelBS;
	bool needRefresh;


	int numSparsePoints;
	int numSparseBufferSize;
    InputPointSparse<MAX_RES_PER_POINT>* originalInputSparse;


	bool bufferValid;
	int numGLBufferPoints;
	int numGLBufferGoodPoints;
	pangolin::GlBuffer vertexBuffer;
	pangolin::GlBuffer colorBuffer;
	
	int object_color[256][3] = {{ 154 , 240 , 251 },
{ 35 , 116 , 206 },
{ 192 , 212 , 219 },
{ 107 , 134 , 22 },
{ 122 , 21 , 77 },
{ 54 , 216 , 246 },
{ 211 , 119 , 142 },
{ 188 , 141 , 92 },
{ 227 , 222 , 137 },
{ 144 , 66 , 135 },
{ 91 , 92 , 2 },
{ 239 , 164 , 103 },
{ 214 , 186 , 240 },
{ 175 , 134 , 122 },
{ 200 , 179 , 166 },
{ 224 , 55 , 9 },
{ 55 , 77 , 185 },
{ 157 , 137 , 189 },
{ 16 , 31 , 87 },
{ 244 , 70 , 120 },
{ 168 , 201 , 69 },
{ 46 , 205 , 167 },
{ 11 , 20 , 53 },
{ 168 , 197 , 117 },
{ 39 , 41 , 209 },
{ 141 , 204 , 243 },
{ 44 , 81 , 192 },
{ 233 , 242 , 162 },
{ 153 , 120 , 103 },
{ 79 , 223 , 193 },
{ 123 , 5 , 254 },
{ 175 , 69 , 162 },
{ 164 , 94 , 112 },
{ 52 , 250 , 85 },
{ 147 , 9 , 72 },
{ 164 , 224 , 62 },
{ 167 , 168 , 227 },
{ 242 , 215 , 254 },
{ 90 , 36 , 84 },
{ 34 , 48 , 182 },
{ 165 , 230 , 157 },
{ 149 , 76 , 244 },
{ 47 , 109 , 14 },
{ 179 , 159 , 124 },
{ 251 , 170 , 98 },
{ 105 , 167 , 195 },
{ 236 , 213 , 100 },
{ 173 , 112 , 179 },
{ 7 , 3 , 86 },
{ 160 , 222 , 98 },
{ 19 , 79 , 47 },
{ 24 , 88 , 56 },
{ 225 , 181 , 197 },
{ 110 , 56 , 176 },
{ 6 , 15 , 242 },
{ 97 , 139 , 121 },
{ 232 , 228 , 96 },
{ 85 , 44 , 223 },
{ 165 , 96 , 205 },
{ 26 , 130 , 148 },
{ 213 , 140 , 93 },
{ 181 , 4 , 129 },
{ 39 , 222 , 202 },
{ 118 , 88 , 206 },
{ 178 , 37 , 108 },
{ 40 , 21 , 182 },
{ 41 , 83 , 254 },
{ 123 , 213 , 157 },
{ 38 , 149 , 55 },
{ 5 , 117 , 76 },
{ 170 , 63 , 243 },
{ 249 , 187 , 111 },
{ 199 , 240 , 159 },
{ 4 , 224 , 239 },
{ 95 , 96 , 78 },
{ 220 , 51 , 237 },
{ 46 , 177 , 134 },
{ 207 , 38 , 44 },
{ 126 , 177 , 92 },
{ 29 , 211 , 119 },
{ 3 , 100 , 10 },
{ 36 , 109 , 236 },
{ 48 , 132 , 159 },
{ 249 , 235 , 4 },
{ 249 , 5 , 58 },
{ 222 , 90 , 83 },
{ 156 , 181 , 237 },
{ 116 , 251 , 139 },
{ 223 , 133 , 237 },
{ 159 , 118 , 98 },
{ 161 , 51 , 40 },
{ 114 , 215 , 102 },
{ 54 , 86 , 74 },
{ 155 , 17 , 130 },
{ 168 , 85 , 108 },
{ 187 , 183 , 101 },
{ 174 , 2 , 175 },
{ 43 , 231 , 225 },
{ 104 , 34 , 126 },
{ 233 , 214 , 36 },
{ 77 , 55 , 0 },
{ 228 , 10 , 209 },
{ 233 , 164 , 88 },
{ 143 , 76 , 247 },
{ 169 , 24 , 101 },
{ 30 , 208 , 101 },
{ 163 , 44 , 56 },
{ 153 , 188 , 50 },
{ 65 , 37 , 30 },
{ 209 , 136 , 5 },
{ 181 , 133 , 53 },
{ 169 , 215 , 225 },
{ 197 , 159 , 75 },
{ 3 , 73 , 212 },
{ 147 , 63 , 12 },
{ 231 , 57 , 159 },
{ 153 , 109 , 32 },
{ 229 , 98 , 82 },
{ 184 , 199 , 160 },
{ 197 , 7 , 21 },
{ 94 , 62 , 109 },
{ 173 , 2 , 35 },
{ 18 , 48 , 154 },
{ 254 , 107 , 86 },
{ 103 , 111 , 216 },
{ 147 , 253 , 227 },
{ 169 , 1 , 240 },
{ 155 , 32 , 193 },
{ 73 , 229 , 5 },
{ 144 , 251 , 2 },
{ 103 , 41 , 36 },
{ 253 , 116 , 221 },
{ 135 , 145 , 84 },
{ 167 , 228 , 197 },
{ 166 , 175 , 252 },
{ 7 , 113 , 101 },
{ 140 , 170 , 72 },
{ 208 , 191 , 151 },
{ 44 , 157 , 164 },
{ 74 , 72 , 45 },
{ 183 , 139 , 179 },
{ 181 , 148 , 228 },
{ 248 , 68 , 230 },
{ 89 , 106 , 223 },
{ 62 , 156 , 96 },
{ 33 , 44 , 142 },
{ 207 , 70 , 241 },
{ 47 , 157 , 211 },
{ 46 , 222 , 225 },
{ 10 , 141 , 191 },
{ 237 , 182 , 80 },
{ 0 , 251 , 241 },
{ 178 , 214 , 113 },
{ 69 , 243 , 205 },
{ 34 , 213 , 161 },
{ 70 , 64 , 24 },
{ 105 , 212 , 162 },
{ 63 , 87 , 75 },
{ 192 , 125 , 159 },
{ 255 , 98 , 121 },
{ 6 , 29 , 123 },
{ 124 , 95 , 115 },
{ 210 , 22 , 253 },
{ 212 , 148 , 192 },
{ 57 , 87 , 231 },
{ 108 , 255 , 49 },
{ 51 , 240 , 74 },
{ 19 , 161 , 124 },
{ 134 , 52 , 218 },
{ 47 , 212 , 189 },
{ 243 , 154 , 127 },
{ 12 , 85 , 150 },
{ 44 , 1 , 132 },
{ 86 , 77 , 65 },
{ 184 , 86 , 154 },
{ 203 , 182 , 28 },
{ 234 , 40 , 118 },
{ 227 , 242 , 78 },
{ 56 , 103 , 54 },
{ 72 , 165 , 218 },
{ 103 , 11 , 235 },
{ 15 , 64 , 18 },
{ 94 , 78 , 84 },
{ 89 , 222 , 247 },
{ 19 , 3 , 180 },
{ 139 , 217 , 238 },
{ 209 , 70 , 234 },
{ 54 , 151 , 237 },
{ 243 , 114 , 64 },
{ 128 , 210 , 153 },
{ 248 , 182 , 119 },
{ 159 , 49 , 216 },
{ 122 , 201 , 17 },
{ 102 , 146 , 154 },
{ 99 , 170 , 212 },
{ 143 , 101 , 82 },
{ 43 , 187 , 110 },
{ 59 , 12 , 11 },
{ 176 , 177 , 132 },
{ 201 , 71 , 58 },
{ 50 , 109 , 109 },
{ 99 , 123 , 190 },
{ 101 , 242 , 108 },
{ 108 , 111 , 5 },
{ 170 , 6 , 21 },
{ 175 , 126 , 81 },
{ 201 , 43 , 153 },
{ 127 , 131 , 229 },
{ 31 , 131 , 112 },
{ 185 , 220 , 136 },
{ 233 , 140 , 130 },
{ 172 , 47 , 1 },
{ 11 , 106 , 35 },
{ 70 , 29 , 89 },
{ 22 , 92 , 253 },
{ 156 , 253 , 35 },
{ 100 , 237 , 204 },
{ 2 , 26 , 7 },
{ 231 , 15 , 241 },
{ 227 , 81 , 132 },
{ 65 , 29 , 206 },
{ 217 , 68 , 133 },
{ 146 , 25 , 99 },
{ 143 , 228 , 15 },
{ 187 , 45 , 54 },
{ 240 , 45 , 105 },
{ 251 , 65 , 35 },
{ 183 , 91 , 29 },
{ 190 , 163 , 149 },
{ 121 , 187 , 132 },
{ 93 , 202 , 28 },
{ 27 , 252 , 77 },
{ 81 , 250 , 221 },
{ 108 , 8 , 183 },
{ 234 , 65 , 78 },
{ 138 , 6 , 85 },
{ 253 , 146 , 163 },
{ 171 , 28 , 162 },
{ 205 , 140 , 53 },
{ 204 , 123 , 133 },
{ 216 , 26 , 25 },
{ 114 , 87 , 120 },
{ 89 , 68 , 56 },
{ 104 , 30 , 51 },
{ 191 , 173 , 176 },
{ 175 , 71 , 8 },
{ 33 , 192 , 40 },
{ 128 , 51 , 73 },
{ 1 , 59 , 227 },
{ 150 , 121 , 13 },
{ 214 , 99 , 176 },
{ 148 , 91 , 227 },
{ 122 , 201 , 43 },
{ 116 , 56 , 12 },
{ 204 , 222 , 237 },
{ 156 , 203 , 218 },
};
};

}
}

