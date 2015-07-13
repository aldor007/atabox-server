#ifndef LRBM_H
#define LRBM_H value
#include "RBM.h"
#include <cstddef>
#include <memory>

using RBMP = std::unique_ptr<RBM>;
struct LRBM // layered RBM
{
    struct Conf
    {
        int max_epoch_ = 20, max_batches_ = 1000, batch_size_ = 30;
    };

    std::vector<RBMP> rbms_;

    RBMP& output_layer() {
        return rbms_[rbms_.size() - 1];
    }

    size_t max_layer() const {
        return rbms_.size();
    }

    int build(const std::vector<int>& layers, const std::vector<int>& adjust = std::vector<int>()) {
        if (layers.size() <= 1)
            return -1;

        for (size_t i=0; i<layers.size() - 1; ++i) {
            int n_visible = layers[i] + (adjust.empty()? 0: adjust[i]);
            int n_hidden = layers[i+1];

        std::cout << "New RBM " << n_visible << " -> " << n_hidden << std::endl;
        rbms_.push_back(std::unique_ptr<RBM>(new RBM(n_visible, n_hidden)));
    }

    return 0;
}

    std::vector<int> offsets(int start) const
    {
        int n_layers = rbms_.size() - start;
        std::vector<int> dims(n_layers + 1);
        dims[0] = 0;
        int total = 0;
        for(size_t i=0; i<n_layers; ++i) {
          total += (rbms_[i + start]->num_visible() + 1) * rbms_[i + start]->num_hidden();
          dims[i+1] = total;
        }
      return dims;
  }

    void to_image(Vector& image, int& width, int& height)
    {
      width = 0; height = 0;
      auto& rbms = this->rbms_;
      for (auto& rbm: rbms) {
          if (width < rbm->num_hidden() + 1)
              width = rbm->num_hidden() + 1;
          height += (rbm->num_visible() + 2);
      }
      image.resize(width * height);

      size_t y_offset = 0;
      for (auto& rbm: rbms) {
          size_t n_visible = rbm->num_visible();
          size_t n_hidden = rbm->num_hidden();
          size_t x_offset = (width - n_hidden) / 2;

          for (size_t j=0; j<n_hidden; ++j)
              image[y_offset * width + x_offset + j] = rbm->bias_hidden_[j];
              for (size_t i=0; i<n_visible; ++i) {
                  for (size_t j=0; j<n_hidden; ++j)
                    // image[(y_offset + i) * width + x_offset + j] = rbm->weight_[i * n_hidden + j];
                    image[(y_offset + i) * width + x_offset + j] = rbm->weight_[j * n_visible+ i];
                    image[(y_offset + i) * width + x_offset + n_hidden] = rbm->bias_visible_[i];
              }
          y_offset += n_visible + 2;
      }
    }

    void store(std::ostream& os) const {
        int32_t count = rbms_.size();
        os.write(reinterpret_cast<char *>(&count), sizeof(count));
        for (auto const& rbm: rbms_)
          rbm->store(os);
    }

    void load(std::istream& is)
    {
        int32_t count = 0;
        is.read(reinterpret_cast<char *>(&count), sizeof(count));

        rbms_.clear();
        for (size_t i = 0; i < count; ++i) {
          RBMP rbm(new RBM());
          rbm->load(is);
          rbms_.push_back(std::move(rbm));
        }
    }
};

#endif
