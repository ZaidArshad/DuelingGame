#include "GLError.hpp"
#include "Logger.hpp"
#include <sstream>
// Used for glDebugMessageCallback
void GLAPIENTRY MessageCallback(GLenum source,
								GLenum type,
								GLuint id,
								GLenum severity,
								GLsizei length,
								const GLchar* message,
								const void* userParam)
{
	if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
	{
		return;
	}

	GLError err = {source, type, id, severity, length, message};
	Logger::log(err);
}