

#include <vulkan/vulkan.hpp>
#include <iostream>

class VulkanUtil {
    public:
        VulkanUtil();
        ~VulkanUtil();
    private:
        bool initialized = false;
    protected:
        bool protected_bool = false;

};
