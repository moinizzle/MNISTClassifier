#include "knn.h"

/**
 * Compilation command
 *    gcc -Wall -std=c99 -lm -o classifier classifier.c knn.c
 *
 * Decompress dataset into individual images:
 *    tar xvzf datasets.tgz
 *
 * Running quick test with 1k training and 1k testing images, K = 1:
 *    ./classifier 1 lists/training_1k.txt lists/testing_1k.txt
 *
 * Running full evaulation with all images, K = 7: (Will take a while)
 *    ./classifier 7 lists/training_full.txt lists/testing_full.txt
 */

/*****************************************************************************/
/* Do not add anything outside the main function here. Any core logic other  */
/* than what is described below should go into `knn.c`. You've been warned!  */
/*****************************************************************************/

/**
 * main() takes in 3 command line arguments:
 *    - K : The K value for K nearest neighbours 
 *    - training_list: Name of a text file with paths to the training images
 *    - testing_list:  Name of a text file with paths to the testing images
 *
 * You need to do the following:
 *    - Parse the command line arguments, call `load_dataset()` appropriately.
 *    - For each test image, call `knn_predict()` and compare with real label
 *    - Print out (only) one integer to stdout representing the number of 
 *        test images that were correctly predicted.
 *    - Free all the data allocated and exit.
 */
int main(int argc, char *argv[]) {

  if (argc != 4){
    return 1;
  }

  //printf("%s\n", argv[0]);



  // TODO: Handle command line arguments
  int k = atoi(argv[1]);
  char *training_list = argv[2];
  char *testing_list = argv[3];

  Dataset *training_data = load_dataset(training_list);
  Dataset *testing_data = load_dataset(testing_list);

  // printf("%d\n", training_data -> num_items);
  // printf("%d\n", testing_data -> num_items);


//     for (int i = 0; i < training_data ->num_items; i++) {
  
//       printf("%d\n", (int) training_data -> images[i].sx);
//       printf("%d\n", (int) training_data -> images[i].sy);
//   printf("%d\n", ds -> labels[i]); 
// }

  // int img = 7;

  // int p;

  // p = knn_predict(training_data, &(testing_data->images[img]), k );
  

  // printf("%s", "label: ");
  // printf("%d\n", testing_data->labels[img]);

  // printf("%s", "prediction: ");
  // printf("%d\n", p);

// for (int i = 0; i < 28*28; i++) {
//   printf("%hhu\n ", testing_data->images[7].data[i]);
//   //printf("%d\n", testing_data->images[7].sx);
//   }



  int total_correct = 0;

  int p;

  for (int i = 0; i <  (testing_data -> num_items); i++) {
    
    p = knn_predict(training_data, &(testing_data->images[i]), k );

    if (p == (int) testing_data->labels[i]){
      total_correct++;
    }
  }

  free_dataset(training_data);
  free_dataset(testing_data);


  // }

//   for (int i = 0; i < num_images; i++) {
    
//     //printf("%d\n", images[i].sx);
//     printf("%d\n", ds -> labels[i]); 
// }

  

  // TODO: Compute the total number of correct predictions
  //int total_correct = 0;

  // Print out answer
  printf("%d\n", total_correct);
  return 0;
}