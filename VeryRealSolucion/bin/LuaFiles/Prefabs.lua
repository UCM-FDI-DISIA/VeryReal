Prefabs={
    {
        name = "PrefabBalaEjemplo",
        components = {
            {
                name = "Transform",
                parameters = {                  
                    position = {0, 0, 0},
                    rotation = {0, 0, 0},
                    scale = {1, 1, 1}     
                }
            },
            {
                name = "MovementBala",
                parameters = {
                    speed = 10,
                    direction = {1, 0, 0}
                }
            }             
        }
    }, 
    {  name = "PrefabPinoEjemplo",
        components = {
	        {
                name = "Transform",
                parameters = {
                    position = {0, 0, 0},
                    rotation = {0, 0, 0},
                    scale = {1, 1, 1}
                }
	        },
            {
                name = "MeshRenderComponent",
                parameters = {
                    
                }
            }
        }
    }
}