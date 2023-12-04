#include "Model.h"


namespace Engine{
Model::Model(){
}

Shader Model::shader = Shader();
bool Model::initialized = false;

Model::Model(std::string modelPath, glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation){
    if(!initialized){
        shader = Shader("shaders/model.vert", "shaders/model.frag");
        initialized = true;
    }

    LoadModel(modelPath);

    CreateBuffers();

    this->pos = pos;
    this->scale = scale;
    this->rotation = rotation;

    UpdateModelMatrix();
}

void Model::LoadModel(std::string path){
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_OptimizeMeshes);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        std::cerr << "Eroror loading model " << path << " ERR: " << std::endl << import.GetErrorString() << std::endl;
        return;
    }

    std::string dir = path.substr(0, path.find_last_of('/')) + "/";


    ProcessNode(scene->mRootNode, scene, dir);

    bool canContinue = false;
        do{
        canContinue = true;
        for(int i = 0; i < threads.size(); i++){
            std::thread& t = threads[i];
            if(!t.joinable()){
                canContinue = false;
            }
            else{

                t.join();
                threads.erase(threads.begin() + i);
                i--;
                
            }
        }
    }while(!canContinue);

    for(Sprite *sprite : sprites){
        sprite->CreateTexture();
    }

}



void Model::ProcessNode(aiNode* node, const aiScene* scene, std::string dir){


    for(uint32_t i = 0; i < node->mNumMeshes; i++){
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        Mesh *modelMesh = new Mesh;
        //vertices uv and normals
        for(uint32_t y = 0; y < mesh->mNumVertices; y++){

            aiVector3D vert = mesh->mVertices[y];
            modelMesh->vertices.push_back(vert.x);
            modelMesh->vertices.push_back(vert.y);
            modelMesh->vertices.push_back(vert.z);

            aiVector3D uv = mesh->mTextureCoords[0][y];
            modelMesh->texCoords.push_back(uv.x);
            modelMesh->texCoords.push_back(uv.y);

            aiVector3D normal = mesh->mNormals[y];
            modelMesh->normals.push_back(normal.x);
            modelMesh->normals.push_back(normal.y);
            modelMesh->normals.push_back(normal.z);



        }
        
        //indices
        for(uint32_t y = 0; y < mesh->mNumFaces; y++){
            aiFace face = mesh->mFaces[y];
            for(uint32_t x = 0; x < face.mNumIndices; x++){
                modelMesh->indices.push_back(face.mIndices[x]);
            }
        }
        
        aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

        aiString baseColorPath;
        mat->GetTexture(aiTextureType_DIFFUSE, 0, &baseColorPath, nullptr, nullptr, nullptr, nullptr, nullptr);

        aiString normalPath;
        mat->GetTexture(aiTextureType_NORMALS, 0, &normalPath, nullptr, nullptr, nullptr, nullptr, nullptr);


        if(spriteMap.count(baseColorPath.C_Str()) == 0){
            sprites.push_back(new Sprite);
            threads.emplace_back(std::ref(sprites[sprites.size()-1][0]), dir +  baseColorPath.C_Str());
            spriteMap[baseColorPath.C_Str()] = sprites.size()-1;
            modelMesh->baseColorSpriteIndex = sprites.size()-1;
        }else{
            modelMesh->baseColorSpriteIndex = spriteMap[baseColorPath.C_Str()];
        }

        aiColor3D baseColor(0.0f, 0.0f, 0.0f);
        mat->Get(AI_MATKEY_COLOR_AMBIENT, baseColor);

        modelMesh->baseColorModifier = glm::vec3(baseColor[0], baseColor[1], baseColor[2]);//todo lighting shit
        if(modelMesh->baseColorModifier == glm::vec3(0)){
            modelMesh->baseColorModifier = glm::vec3(1);
        }

        if(spriteMap.count(normalPath.C_Str()) == 0){
            sprites.push_back(new Sprite);
            threads.emplace_back(std::ref(sprites[sprites.size()-1][0]), dir +  normalPath.C_Str());
            spriteMap[normalPath.C_Str()] = sprites.size()-1;
            modelMesh->normalSpriteIndex = sprites.size()-1;
        }
        else{
            modelMesh->normalSpriteIndex = spriteMap[normalPath.C_Str()];
        }
        meshes.push_back(modelMesh);
    }

    for(uint32_t i = 0; i < node->mNumChildren; i++){
        ProcessNode(node->mChildren[i], scene, dir);
    }
}

void Model::CreateBuffers()
{

    
    for (Mesh *mesh : meshes)
    {
        glCreateVertexArrays(1, &mesh->VAO);
        glBindVertexArray(mesh->VAO);

        glCreateBuffers(1, &mesh->VBO);
        glCreateBuffers(1, &mesh->EBO);
        glCreateBuffers(1, &mesh->uvVBO);
        glCreateBuffers(1, &mesh->normalVBO);


        glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->vertices.size(), mesh->vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->indices.size(), mesh->indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)(0));

        glBindBuffer(GL_ARRAY_BUFFER, mesh->uvVBO);
        glBufferData(GL_ARRAY_BUFFER, mesh->texCoords.size() * sizeof(float), mesh->texCoords.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)(0));

        glBindBuffer(GL_ARRAY_BUFFER, mesh->normalVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->normals.size(), mesh->normals.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)(0));



        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);

        mesh->indiceCount = mesh->indices.size();

        mesh->vertices.clear();
        mesh->normals.clear();
        mesh->texCoords.clear();
        mesh->indices.clear();
    }
}

void Model::Draw()
{

    for (Mesh *mesh : meshes)
    {
        glBindVertexArray(mesh->VAO);

        shader.Use();

        sprites[mesh->baseColorSpriteIndex]->BindTexture(GL_TEXTURE0);
        sprites[mesh->normalSpriteIndex]->BindTexture(GL_TEXTURE1);

        glUniform1i(shader.GetUniformLoc("baseTex"), 0);
        glUniform1i(shader.GetUniformLoc("normalTex"), 1);
        glUniform3fv(shader.GetUniformLoc("colorModifier"), 1, glm::value_ptr(mesh->baseColorModifier));
        glUniformMatrix4fv(shader.GetUniformLoc("model"), 1, GL_FALSE, glm::value_ptr(model));

        Camera::ApplyViewProjectionMatrix(shader);

        Light::ApplyGlobalLight(shader);

        glDrawElements(GL_TRIANGLES, mesh->indiceCount, GL_UNSIGNED_INT, nullptr);
    }
}

void Model::SetPosition(glm::vec3 pos){
    this->pos = pos;
    UpdateModelMatrix();
}

void Model::SetScale(glm::vec3 scale){
    this->scale = scale;
    UpdateModelMatrix();
}

void Model::SetRotation(glm::vec3 rotation){
    this->rotation = rotation;
    UpdateModelMatrix();
}

void Model::UpdateModelMatrix(){
    model = glm::mat4(1.0f);

    model = glm::translate(model, pos);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    model = glm::scale(model, scale);
}

}
