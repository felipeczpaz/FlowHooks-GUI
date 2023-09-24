#pragma once

#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p) = NULL; } }
#define SAFE_DELETE(p) { if(p) { delete (p); (p) = NULL; } }
