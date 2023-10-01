#pragma once

#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p) = nullptr; } }
#define SAFE_DELETE(p) { if(p) { delete (p); (p) = nullptr; } }
