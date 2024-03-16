Entities={
    {
        name = "Player",
        components = {
            {
                name = "Transform",
                parameters = {                  
                    position = {10, 5, 1},
                    rotation ={0, 0, 0},
                    scale = {1, 1, 1}                   
                },
            },                
        }
    }, 
    {  name = "Ogreman",
        components = {
	        {
                name = "Transform",
                parameters = {
                    position = {100, 57, 15},
                    rotation = {90, 0, 0},
                    scale = {1, 1, 1}
                }
	        }, 
            {
                name = "MeshRenderComponent",
                parameters = {                  
                    isstatic = false,
                    modelname = "Ogreman.mesh",
                    entityname= "Ogreman",
                    materialname = "Ogreman.mat"
                }
            }       
        }
    }
}