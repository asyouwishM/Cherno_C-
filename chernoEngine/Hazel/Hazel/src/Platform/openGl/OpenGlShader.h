#pragma once
#include "Hazel/Renderer/Shader.h"

typedef unsigned int GLenum;

namespace Hazel
{

	class OpenGlShader:public Shader
	{
	public:
		OpenGlShader(const std::string& filepath);
		OpenGlShader(const std ::string& name , const std::string& vertexsrc, const std::string& fragmentsrc);

		~OpenGlShader();

		//Bind,Unbind just for debug mode
		virtual void Bind() const ;
		virtual void UnBind()const;

		virtual void SetMat4(const std::string& name, const glm::mat4& mat4) override;
		virtual void SetMat3(const std::string& name, const glm::mat3& mat3)override;
												
		virtual void SetFloat4(const std::string& name, const glm::vec4& vec4)override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& vec3)override;
		virtual void SetFloat2(const std::string& name, const glm::vec2& vec2)override;
		virtual void SetFloat(const std::string& name, float value) override;


		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetIntArray(const std::string& name, int* value , uint32_t count) override;


		inline virtual const std::string& Getname() const { return m_name; }


		void UploadUniformInt(const std::string& name,  int mat) ; 
		void UploadUniformIntArray(const std::string& name, int* value, uint32_t count) ;

		void UploadUniformFloat(const std::string& name,  float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& vec);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& vec);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& vec);

		void UploadUniformMat3(const std::string& name, const glm::mat3& mat);
		void UploadUniformMat4(const std::string& name, const glm::mat4& mat);
		
	private:

		std::string readFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> preProcess(const std::string& source);
		void shaderCompile(const std::unordered_map<GLenum, std::string>& shaderSource);

		void CompileOrGetVulkanBinaries(const std::unordered_map<GLenum, std::string>& shaderSources);
		void CompileOrGetOpenGLBinaries();
		void CreateProgram();
		void Reflect(GLenum stage, const std::vector<uint32_t>& shaderData);


	private:
		unsigned int m_rendererID;
		std::string m_filePath;
		std::string m_name;


		std::unordered_map<GLenum, std::vector<uint32_t>> m_VulkanSPIRV;
		std::unordered_map<GLenum, std::vector<uint32_t>> m_OpenGLSPIRV;

		std::unordered_map<GLenum, std::string> m_OpenGLSourceCode;
	
	};
}


