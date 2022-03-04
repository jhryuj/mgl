% mglMetalCreateTexture.m
%
%       usage: [tex, ackTime, processedTime] = mglMetalCreateTexture(im)
%          by: justin gardner
%        date: 09/28/2021
%  copyright: (c) 2021 Justin Gardner (GPL see mgl/COPYING)
%     purpose: Private mglMetal function to send texture information
%              to mglMetal application and return a structure to be
%              used with mglMetalBltTexture to display - these
%              functions are called by mglCreateTexture and mglBltTexture
%       e.g.:
%
function [tex, ackTime, processedTime] = mglMetalCreateTexture(im)

global mgl

[tex.imageWidth, tex.imageHeight, tex.colorDim] = size(im);

% for now, imageWidth needs to be 16 byte aligned to 256
imageWidth = ceil(tex.imageWidth*16/256)*16;
if imageWidth ~= tex.imageWidth
  disp('(mglMetalCreateTexture) Resizing texture image to align to 256')
  newim = zeros([imageWidth tex.imageHeight tex.colorDim]);
  newim(1:tex.imageWidth,1:tex.imageHeight,:) = im;
  % and reset to this new padded image
  im = newim;
  tex.imageWidth = imageWidth;
end

% Rearrange the image data to Metal texture format.
% See the corresponding shift in mglMetalReadTexture.
im = shiftdim(im,2);

% send texture command
mglSocketWrite(mgl.s, mgl.command.mglCreateTexture);
ackTime = mglSocketRead(mgl.s, 'double');
mglSocketWrite(mgl.s, uint32(tex.imageWidth));
mglSocketWrite(mgl.s, uint32(tex.imageHeight));
mglSocketWrite(mgl.s, single(im(:)));
tex.textureNumber = mglSocketRead(mgl.s, 'uint32');
numTextures = mglSocketRead(mgl.s, 'uint32');
processedTime = mglSocketRead(mgl.s, 'double');

% set the textureType (this was used in openGL to differntiate 1D and 2D textures)
tex.textureType = 1;

mglSetParam('numTextures', numTextures);
