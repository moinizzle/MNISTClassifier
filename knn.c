#include "knn.h"
#include <limits.h>

int compare(const void* n1, const void* n2);

/**
 * This function takes in the name of the text file containing the image names
 * This function should NOT assume anything about the image resolutions,
 * and may be tested with images of different sizes. You will need to allocate
 * your own data for the struct, and also for the images / labels.
 */
Dataset *load_dataset(const char *filename) {
  // TODO: Allocate data, read image data / labels, return


  FILE *fp = fopen(filename, "rb");
    if (!fp) {
      exit(1);
  }


  int num_images = 0;


  char buf[200];
  while(fgets(buf,sizeof(buf), fp) != NULL){
  num_images++;
  }

  //printf("%d", num_images);

  //Image images[num_images];

  
  Image *images = malloc(sizeof(Image)*num_images);

  unsigned char *labels = malloc(sizeof(unsigned char)*num_images);

  //unsigned char labels[num_images];

  fseek(fp, 0, SEEK_SET);
  char img_file[1000];


  int img_i = 0;

  while(fscanf(fp, "%s\n", img_file) == 1) {

    char label[100];

    memset(label, '\0', sizeof(label));
    strcpy(label, img_file);
    
    char * token = strtok(label, "-");
    token = strtok(NULL, ".");

    labels[img_i] = (unsigned char) atoi(token);

    // printf("%d\n", labels[img_i]);
  
    //images[img_i] = malloc(sizeof(Image));


    FILE *fpi = fopen(img_file, "rb");
  
    if (!fpi) {
      printf("File does not exist\n"); 
      exit(1);
      //return;   
    }

    // end of line 
    while(getc(fpi) != '\n');
    fseek(fpi, -1, SEEK_CUR);  
    // Read the image dimensions

    // images[img_i] = NULL;
    // images[img_i].sy = NULL;

    int sx, sy;

    fscanf(fpi, "%d %d", &sx , &sy );

    images[img_i].sx = sx;
    images[img_i].sy = sy;
    
    

    // printf("%s\n", img_file);
    // printf("%d\n", images[img_i] .sx);
    // printf("%d\n", img->sy);
  
    images[img_i].data = (unsigned char*) malloc( (sx * sy) * sizeof(unsigned char)); 
  
    //unsigned char word;

    int dim;

    fscanf(fpi, "%d\n" ,&dim);
    
    unsigned char pixel;
    int p_i=0;
    
    while(!feof(fpi)){
      fscanf(fpi, "%hhu", &pixel);
      p_i++;
      images[img_i].data[p_i] = pixel;
}

  
    //images[img_i] = img;

    //free(img);
    img_i++;
    fclose(fpi);

  }

  fclose(fp);

  
  Dataset *ds = malloc(sizeof(Dataset));
  //ds -> num_items = (*int) malloc(sizeof(int));
  ds -> num_items = num_images;
  ds -> images = malloc(sizeof(Image)*num_images);
  ds->images = images;
  ds -> labels = malloc(num_images* sizeof(int));
  //memcpy(ds-> labels, labels, sizeof labels);

  ds-> labels = labels;

  //double d = distance(&images[0] , &images[1] );

  // /printf("%f\n", d);

//   for (int i = 0; i < num_images; i++) {
  
//   //printf("%d\n", ds -> images[i].sx);
//   //printf("%d\n", ds -> labels[i]); 
// }
  
  return ds;
}


// doesn't check image sizes for rest of the functions
// assume all images sizes are the same size

/** 
 * Return the euclidean distance between the image pixels (as vectors).
 */
double distance(Image *a, Image *b) {

  float euclid = 0;
  int i = 0;


  int size = (int) ((a -> sx) * (a -> sy));


  while (i < size ){
    euclid += pow( (int) a->data[i] -  (int) b->data[i], 2);
    i++;
  }

  return (double) sqrt(euclid);
} 

/**
 * Given the input training dataset, an image to classify and K,
 *   (1) Find the K most similar images to `input` in the dataset
 *   (2) Return the most frequent label of these K images
 * 
 * Note: If there's multiple images with the same smallest values, pick the
 *      ones that come first. For automarking we will make sure the K smallest
 *      ones are unique, so it doesn't really matter.
 */ 
int knn_predict(Dataset *data, Image *input, int K) {
  // TODO: Replace this with predicted label (0-9)
  
  
  int i;

  int n = data -> num_items;
  //double distances[n];

  double *distances = malloc(sizeof(double)*n);
  
  //printf("%d\n", n);
  
  for(i=0; i < n ; i++) {
    distances[i] = (double) distance(input, &(data->images[i]) );
    //printf("%f\n", distances[i]);  
  }

  int *k_values = malloc(sizeof(int)*K);
  
  int k_count = 0;

  while (k_count < K){
        int a = 0;
        int index = 0;
    
    for (a = 1; a < n; a++){
      if (distances[a] < distances[index]) 
        index= a;
    }

    //printf("%d\n", k);
    //printf("%f\n", distances[index]);
    distances[index] = INT_MAX;
    k_values[k_count] = (int) data->labels[index];
    k_count++;
  }

  free(distances);

  // for (int i = 0; i < K; i++) {
  //   printf("%f\n", k_values[i]);
  // }


  qsort(k_values, K , sizeof(int), compare);

  // for (int i = 0; i < K; i++) {
  //   printf("%d\n", k_values[i]);
  // }

    int most_popular_k = k_values[0];
    int c, tc, dummy;
    dummy = c = tc = 0;
    
    for(int i = 0; i < K; i++) { 
        dummy = k_values[i];
        tc = 0;
        
        for(int j = i+1; j < K; j++) {
            
            if(k_values[j] == dummy) {
                tc++;
            }
        }

        if(tc > c) {
            most_popular_k = dummy;
            c = tc;
        }
    }

  free(k_values);

  return most_popular_k;

  //return -1;
}

/** 
 * Free all the allocated memory for the dataset
 */
void free_dataset(Dataset *data) {
  // TODO: free data

  free(data->images);
  free(data->labels);
  //free(data->num_items);
  free(data);

}

int compare(const void* n1, const void* n2){
    
    int x = *((int*) n1);
    int y = *((int*) n2);
    
    return (int) (y - x);
}