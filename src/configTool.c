#include"configTool.h"


int loadConfigFile(char *configFileName){
	FILE *configFile;
	printf("Loading config file...\n");
	
	configFile = fopen(configFileName, "r");
	if(configFile == NULL){
		printf("Error while opening config file on location \"%s\"\n", configFileName);
		return 1;
	}
	printf("File loaded succesfully...\n");

	char *line = NULL;
    size_t len = 0;
    ssize_t read;
	char buffer[25];
	while ((read = getline(&line, &len, configFile)) != -1) {
		if(sscanf(line, "frequency:%d", &(config.freq))){
			continue;
		}
		if(sscanf(line, "bandwidth:%d", &(config.bandwidth))){
			continue;
		}
		if(sscanf(line, "module:%s", buffer)){
			config.module = strdup(buffer);
			continue;
		}
		if(sscanf(line, "apid:%d", &(config.apid))){
			continue;
		}
		if(sscanf(line, "vpid:%d", &(config.vpid))){
			continue;
		}
		if(sscanf(line, "atype:%s", buffer)){
			config.atype = strdup(buffer);
			continue;
		}
		if(sscanf(line, "vtype:%s", buffer)){
			config.vtype = strdup(buffer);
			continue;
		}
		if(sscanf(line, "rating:%d", &(config.rating))){
			continue;
		}		
		if(sscanf(line, "password:%d", &(config.password))){
			continue;
		}
    }
	printf("Loaded config data:\n");
	printf("\tFREQ: %d\n", config.freq);
	printf("\tBANDWIDTH: %d\n", config.bandwidth);
	printf("\tMODULE: %s\n", config.module);
	printf("\tAudio PID: %d\n", config.apid);
	printf("\tVideo PID: %d\n", config.vpid);
	printf("\tAudio type: %s\n", config.atype);
	printf("\tVideo type: %s\n", config.vtype);
	printf("\tRATING: %d\n", config.rating);
	printf("\tPASSWORD: %d\n", config.password);
	
	fclose(configFile);
    if (line){
		free(line);
	}
        
	return 0;
}
