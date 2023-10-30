
#include <opencv2/features2d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>

#include "hdf5.h"

#include <cstdio>
#include <string>
#include <ctime>
#include <cstdlib>


int main(int argc, char** argv)
{
    // usage: ./akaze <img1> <img2> <outfile>
    // <img1> and <img2> are the input images
    // <outfile> is the output file where the homography is placed

    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <img1> <img2> <outfile>\n", argv[0]);
        return 1;
    }

    srand(time(nullptr));

    // Read the images
    cv::Mat img1 = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    cv::Mat img2 = cv::imread(argv[2], cv::IMREAD_GRAYSCALE);

    if (img1.empty())
    {
        fprintf(stderr, "Could not open image %s\n", argv[1]);
        return 1;
    }
    if (img2.empty())
    {
        fprintf(stderr, "Could not open image %s\n", argv[2]);
        return 1;
    }

    // resize the images to 5500x5500, for testing speed
    cv::resize(img1, img1, cv::Size(5500, 5500));
    cv::resize(img2, img2, cv::Size(5500, 5500));

    // Detect the keypoints using AKAZE
    std::vector<cv::KeyPoint> kpts1, kpts2;

    cv::Ptr<cv::AKAZE> akaze = cv::AKAZE::create();
    akaze->detect(img1, kpts1);
    akaze->detect(img2, kpts2);

    // Compute the descriptors
    cv::Mat desc1, desc2;

    akaze->compute(img1, kpts1, desc1);
    akaze->compute(img2, kpts2, desc2);

    // Match the descriptors using brute force
    cv::BFMatcher matcher(cv::NORM_HAMMING);
    std::vector<cv::DMatch> matches;
    matcher.match(desc1, desc2, matches);

    // Sort the matches by distance, smallest first
    std::sort(matches.begin(), matches.end());

    // Compute homography using RANSAC, selecting the best 20% matches
    std::vector<cv::Point2f> src_pts, dst_pts;
    size_t n = (size_t)((double)matches.size() * 0.2);
    src_pts.reserve(n); dst_pts.reserve(n);
    for (size_t i = 0; i < n; i++)
    {
        src_pts.push_back(kpts1[matches[i].queryIdx].pt);
        dst_pts.push_back(kpts2[matches[i].trainIdx].pt);
    }

    cv::Mat mask;
    cv::Mat H = cv::findHomography(src_pts, dst_pts, cv::RANSAC, 5.0, mask, 2000, 0.995);

    // Write the homography to the output file
    hid_t file = H5Fcreate(argv[3], H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // three datasets, {img1, img2, homography}
    // img1 and img2 are variable length null-terminated strings
    // homography is a 3x3 matrix of type double
    hid_t strtype = H5Tcopy(H5T_C_S1);
    H5Tset_size(strtype, strlen(argv[1]) + 1);

    hsize_t dims[1] = {1};
    hid_t space = H5Screate_simple(1, dims, NULL);
    hid_t dset = H5Dcreate(file, "img1", strtype, space, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    H5Dwrite(dset, strtype, H5S_ALL, H5S_ALL, H5P_DEFAULT, argv[1]);
    H5Sclose(space);

    space = H5Screate_simple(1, dims, NULL);
    dset = H5Dcreate(file, "img2", strtype, space, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    H5Dwrite(dset, strtype, H5S_ALL, H5S_ALL, H5P_DEFAULT, argv[2]);
    H5Sclose(space);
    H5Tclose(strtype);

    hsize_t dims2[2] = {3, 3};
    space = H5Screate_simple(2, dims2, NULL);
    dset = H5Dcreate(file, "homography", H5T_NATIVE_DOUBLE, space, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    H5Dwrite(dset, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, H.data);
    H5Sclose(space);

    H5Dclose(dset);
    H5Fclose(file);

    return 0;
}



