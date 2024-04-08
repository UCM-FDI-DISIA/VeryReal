Entities={
    {
        name = "Lightt",
        components = {
            {
                name = "Transform",
                parameters = {                  
                    position = {10, 5, 1},
                    rotation ={0, 0, 0},
                    scale = {1, 1, 1}                   
                },
                name = "Light",
                parameters = {                  
                   type=1,
                   diffusecolour={1,1,1},
                   shadowfardist=25.0,
                   shadowdist=25.0,
                   ineerangle=90.0,
                   outerangle=180.0,
                   nearclipdist=0.1,
                   shdws=true

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
                    modelname = "Sinbad.mesh",
                    entityname= "sinbad",
                    materialname = ""
                }
            }       
        }
    }
}