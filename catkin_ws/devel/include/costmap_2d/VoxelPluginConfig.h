//#line 2 "/opt/ros/noetic/share/dynamic_reconfigure/cmake/../templates/ConfigType.h.template"
// *********************************************************
//
// File autogenerated for the costmap_2d package
// by the dynamic_reconfigure package.
// Please do not edit.
//
// ********************************************************/

#ifndef __costmap_2d__VOXELPLUGINCONFIG_H__
#define __costmap_2d__VOXELPLUGINCONFIG_H__

#if __cplusplus >= 201103L
#define DYNAMIC_RECONFIGURE_FINAL final
#else
#define DYNAMIC_RECONFIGURE_FINAL
#endif

#include <dynamic_reconfigure/config_tools.h>
#include <limits>
#include <ros/node_handle.h>
#include <dynamic_reconfigure/ConfigDescription.h>
#include <dynamic_reconfigure/ParamDescription.h>
#include <dynamic_reconfigure/Group.h>
#include <dynamic_reconfigure/config_init_mutex.h>
#include <boost/any.hpp>

namespace costmap_2d
{
  class VoxelPluginConfigStatics;

  class VoxelPluginConfig
  {
  public:
    class AbstractParamDescription : public dynamic_reconfigure::ParamDescription
    {
    public:
      AbstractParamDescription(std::string n, std::string t, uint32_t l,
          std::string d, std::string e)
      {
        name = n;
        type = t;
        level = l;
        description = d;
        edit_method = e;
      }
      virtual ~AbstractParamDescription() = default;

      virtual void clamp(VoxelPluginConfig &config, const VoxelPluginConfig &max, const VoxelPluginConfig &min) const = 0;
      virtual void calcLevel(uint32_t &level, const VoxelPluginConfig &config1, const VoxelPluginConfig &config2) const = 0;
      virtual void fromServer(const ros::NodeHandle &nh, VoxelPluginConfig &config) const = 0;
      virtual void toServer(const ros::NodeHandle &nh, const VoxelPluginConfig &config) const = 0;
      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, VoxelPluginConfig &config) const = 0;
      virtual void toMessage(dynamic_reconfigure::Config &msg, const VoxelPluginConfig &config) const = 0;
      virtual void getValue(const VoxelPluginConfig &config, boost::any &val) const = 0;
    };

    typedef boost::shared_ptr<AbstractParamDescription> AbstractParamDescriptionPtr;
    typedef boost::shared_ptr<const AbstractParamDescription> AbstractParamDescriptionConstPtr;

    // Final keyword added to class because it has virtual methods and inherits
    // from a class with a non-virtual destructor.
    template <class T>
    class ParamDescription DYNAMIC_RECONFIGURE_FINAL : public AbstractParamDescription
    {
    public:
      ParamDescription(std::string a_name, std::string a_type, uint32_t a_level,
          std::string a_description, std::string a_edit_method, T VoxelPluginConfig::* a_f) :
        AbstractParamDescription(a_name, a_type, a_level, a_description, a_edit_method),
        field(a_f)
      {}

      T VoxelPluginConfig::* field;

      virtual void clamp(VoxelPluginConfig &config, const VoxelPluginConfig &max, const VoxelPluginConfig &min) const override
      {
        if (config.*field > max.*field)
          config.*field = max.*field;

        if (config.*field < min.*field)
          config.*field = min.*field;
      }

      virtual void calcLevel(uint32_t &comb_level, const VoxelPluginConfig &config1, const VoxelPluginConfig &config2) const override
      {
        if (config1.*field != config2.*field)
          comb_level |= level;
      }

      virtual void fromServer(const ros::NodeHandle &nh, VoxelPluginConfig &config) const override
      {
        nh.getParam(name, config.*field);
      }

      virtual void toServer(const ros::NodeHandle &nh, const VoxelPluginConfig &config) const override
      {
        nh.setParam(name, config.*field);
      }

      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, VoxelPluginConfig &config) const override
      {
        return dynamic_reconfigure::ConfigTools::getParameter(msg, name, config.*field);
      }

      virtual void toMessage(dynamic_reconfigure::Config &msg, const VoxelPluginConfig &config) const override
      {
        dynamic_reconfigure::ConfigTools::appendParameter(msg, name, config.*field);
      }

      virtual void getValue(const VoxelPluginConfig &config, boost::any &val) const override
      {
        val = config.*field;
      }
    };

    class AbstractGroupDescription : public dynamic_reconfigure::Group
    {
      public:
      AbstractGroupDescription(std::string n, std::string t, int p, int i, bool s)
      {
        name = n;
        type = t;
        parent = p;
        state = s;
        id = i;
      }

      virtual ~AbstractGroupDescription() = default;

      std::vector<AbstractParamDescriptionConstPtr> abstract_parameters;
      bool state;

      virtual void toMessage(dynamic_reconfigure::Config &msg, const boost::any &config) const = 0;
      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, boost::any &config) const =0;
      virtual void updateParams(boost::any &cfg, VoxelPluginConfig &top) const= 0;
      virtual void setInitialState(boost::any &cfg) const = 0;


      void convertParams()
      {
        for(std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = abstract_parameters.begin(); i != abstract_parameters.end(); ++i)
        {
          parameters.push_back(dynamic_reconfigure::ParamDescription(**i));
        }
      }
    };

    typedef boost::shared_ptr<AbstractGroupDescription> AbstractGroupDescriptionPtr;
    typedef boost::shared_ptr<const AbstractGroupDescription> AbstractGroupDescriptionConstPtr;

    // Final keyword added to class because it has virtual methods and inherits
    // from a class with a non-virtual destructor.
    template<class T, class PT>
    class GroupDescription DYNAMIC_RECONFIGURE_FINAL : public AbstractGroupDescription
    {
    public:
      GroupDescription(std::string a_name, std::string a_type, int a_parent, int a_id, bool a_s, T PT::* a_f) : AbstractGroupDescription(a_name, a_type, a_parent, a_id, a_s), field(a_f)
      {
      }

      GroupDescription(const GroupDescription<T, PT>& g): AbstractGroupDescription(g.name, g.type, g.parent, g.id, g.state), field(g.field), groups(g.groups)
      {
        parameters = g.parameters;
        abstract_parameters = g.abstract_parameters;
      }

      virtual bool fromMessage(const dynamic_reconfigure::Config &msg, boost::any &cfg) const override
      {
        PT* config = boost::any_cast<PT*>(cfg);
        if(!dynamic_reconfigure::ConfigTools::getGroupState(msg, name, (*config).*field))
          return false;

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          boost::any n = &((*config).*field);
          if(!(*i)->fromMessage(msg, n))
            return false;
        }

        return true;
      }

      virtual void setInitialState(boost::any &cfg) const override
      {
        PT* config = boost::any_cast<PT*>(cfg);
        T* group = &((*config).*field);
        group->state = state;

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          boost::any n = boost::any(&((*config).*field));
          (*i)->setInitialState(n);
        }

      }

      virtual void updateParams(boost::any &cfg, VoxelPluginConfig &top) const override
      {
        PT* config = boost::any_cast<PT*>(cfg);

        T* f = &((*config).*field);
        f->setParams(top, abstract_parameters);

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          boost::any n = &((*config).*field);
          (*i)->updateParams(n, top);
        }
      }

      virtual void toMessage(dynamic_reconfigure::Config &msg, const boost::any &cfg) const override
      {
        const PT config = boost::any_cast<PT>(cfg);
        dynamic_reconfigure::ConfigTools::appendGroup<T>(msg, name, id, parent, config.*field);

        for(std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = groups.begin(); i != groups.end(); ++i)
        {
          (*i)->toMessage(msg, config.*field);
        }
      }

      T PT::* field;
      std::vector<VoxelPluginConfig::AbstractGroupDescriptionConstPtr> groups;
    };

class DEFAULT
{
  public:
    DEFAULT()
    {
      state = true;
      name = "Default";
    }

    void setParams(VoxelPluginConfig &config, const std::vector<AbstractParamDescriptionConstPtr> params)
    {
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator _i = params.begin(); _i != params.end(); ++_i)
      {
        boost::any val;
        (*_i)->getValue(config, val);

        if("enabled"==(*_i)->name){enabled = boost::any_cast<bool>(val);}
        if("footprint_clearing_enabled"==(*_i)->name){footprint_clearing_enabled = boost::any_cast<bool>(val);}
        if("max_obstacle_height"==(*_i)->name){max_obstacle_height = boost::any_cast<double>(val);}
        if("origin_z"==(*_i)->name){origin_z = boost::any_cast<double>(val);}
        if("z_resolution"==(*_i)->name){z_resolution = boost::any_cast<double>(val);}
        if("z_voxels"==(*_i)->name){z_voxels = boost::any_cast<int>(val);}
        if("unknown_threshold"==(*_i)->name){unknown_threshold = boost::any_cast<int>(val);}
        if("mark_threshold"==(*_i)->name){mark_threshold = boost::any_cast<int>(val);}
        if("combination_method"==(*_i)->name){combination_method = boost::any_cast<int>(val);}
      }
    }

    bool enabled;
bool footprint_clearing_enabled;
double max_obstacle_height;
double origin_z;
double z_resolution;
int z_voxels;
int unknown_threshold;
int mark_threshold;
int combination_method;

    bool state;
    std::string name;

    
}groups;



//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      bool enabled;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      bool footprint_clearing_enabled;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double max_obstacle_height;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double origin_z;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      double z_resolution;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      int z_voxels;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      int unknown_threshold;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      int mark_threshold;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      int combination_method;
//#line 231 "/opt/ros/noetic/share/dynamic_reconfigure/cmake/../templates/ConfigType.h.template"

    bool __fromMessage__(dynamic_reconfigure::Config &msg)
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();

      int count = 0;
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        if ((*i)->fromMessage(msg, *this))
          count++;

      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); i ++)
      {
        if ((*i)->id == 0)
        {
          boost::any n = boost::any(this);
          (*i)->updateParams(n, *this);
          (*i)->fromMessage(msg, n);
        }
      }

      if (count != dynamic_reconfigure::ConfigTools::size(msg))
      {
        ROS_ERROR("VoxelPluginConfig::__fromMessage__ called with an unexpected parameter.");
        ROS_ERROR("Booleans:");
        for (unsigned int i = 0; i < msg.bools.size(); i++)
          ROS_ERROR("  %s", msg.bools[i].name.c_str());
        ROS_ERROR("Integers:");
        for (unsigned int i = 0; i < msg.ints.size(); i++)
          ROS_ERROR("  %s", msg.ints[i].name.c_str());
        ROS_ERROR("Doubles:");
        for (unsigned int i = 0; i < msg.doubles.size(); i++)
          ROS_ERROR("  %s", msg.doubles[i].name.c_str());
        ROS_ERROR("Strings:");
        for (unsigned int i = 0; i < msg.strs.size(); i++)
          ROS_ERROR("  %s", msg.strs[i].name.c_str());
        // @todo Check that there are no duplicates. Make this error more
        // explicit.
        return false;
      }
      return true;
    }

    // This version of __toMessage__ is used during initialization of
    // statics when __getParamDescriptions__ can't be called yet.
    void __toMessage__(dynamic_reconfigure::Config &msg, const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__, const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__) const
    {
      dynamic_reconfigure::ConfigTools::clear(msg);
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->toMessage(msg, *this);

      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); ++i)
      {
        if((*i)->id == 0)
        {
          (*i)->toMessage(msg, *this);
        }
      }
    }

    void __toMessage__(dynamic_reconfigure::Config &msg) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();
      __toMessage__(msg, __param_descriptions__, __group_descriptions__);
    }

    void __toServer__(const ros::NodeHandle &nh) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->toServer(nh, *this);
    }

    void __fromServer__(const ros::NodeHandle &nh)
    {
      static bool setup=false;

      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->fromServer(nh, *this);

      const std::vector<AbstractGroupDescriptionConstPtr> &__group_descriptions__ = __getGroupDescriptions__();
      for (std::vector<AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); i++){
        if (!setup && (*i)->id == 0) {
          setup = true;
          boost::any n = boost::any(this);
          (*i)->setInitialState(n);
        }
      }
    }

    void __clamp__()
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      const VoxelPluginConfig &__max__ = __getMax__();
      const VoxelPluginConfig &__min__ = __getMin__();
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->clamp(*this, __max__, __min__);
    }

    uint32_t __level__(const VoxelPluginConfig &config) const
    {
      const std::vector<AbstractParamDescriptionConstPtr> &__param_descriptions__ = __getParamDescriptions__();
      uint32_t level = 0;
      for (std::vector<AbstractParamDescriptionConstPtr>::const_iterator i = __param_descriptions__.begin(); i != __param_descriptions__.end(); ++i)
        (*i)->calcLevel(level, config, *this);
      return level;
    }

    static const dynamic_reconfigure::ConfigDescription &__getDescriptionMessage__();
    static const VoxelPluginConfig &__getDefault__();
    static const VoxelPluginConfig &__getMax__();
    static const VoxelPluginConfig &__getMin__();
    static const std::vector<AbstractParamDescriptionConstPtr> &__getParamDescriptions__();
    static const std::vector<AbstractGroupDescriptionConstPtr> &__getGroupDescriptions__();

  private:
    static const VoxelPluginConfigStatics *__get_statics__();
  };

  template <> // Max and min are ignored for strings.
  inline void VoxelPluginConfig::ParamDescription<std::string>::clamp(VoxelPluginConfig &config, const VoxelPluginConfig &max, const VoxelPluginConfig &min) const
  {
    (void) config;
    (void) min;
    (void) max;
    return;
  }

  class VoxelPluginConfigStatics
  {
    friend class VoxelPluginConfig;

    VoxelPluginConfigStatics()
    {
VoxelPluginConfig::GroupDescription<VoxelPluginConfig::DEFAULT, VoxelPluginConfig> Default("Default", "", 0, 0, true, &VoxelPluginConfig::groups);
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.enabled = 0;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.enabled = 1;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.enabled = 1;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(VoxelPluginConfig::AbstractParamDescriptionConstPtr(new VoxelPluginConfig::ParamDescription<bool>("enabled", "bool", 0, "Whether to use this plugin or not", "", &VoxelPluginConfig::enabled)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(VoxelPluginConfig::AbstractParamDescriptionConstPtr(new VoxelPluginConfig::ParamDescription<bool>("enabled", "bool", 0, "Whether to use this plugin or not", "", &VoxelPluginConfig::enabled)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.footprint_clearing_enabled = 0;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.footprint_clearing_enabled = 1;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.footprint_clearing_enabled = 1;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(VoxelPluginConfig::AbstractParamDescriptionConstPtr(new VoxelPluginConfig::ParamDescription<bool>("footprint_clearing_enabled", "bool", 0, "Whether to clear the robot's footprint of lethal obstacles", "", &VoxelPluginConfig::footprint_clearing_enabled)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(VoxelPluginConfig::AbstractParamDescriptionConstPtr(new VoxelPluginConfig::ParamDescription<bool>("footprint_clearing_enabled", "bool", 0, "Whether to clear the robot's footprint of lethal obstacles", "", &VoxelPluginConfig::footprint_clearing_enabled)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.max_obstacle_height = 0.0;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.max_obstacle_height = 50.0;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.max_obstacle_height = 2.0;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(VoxelPluginConfig::AbstractParamDescriptionConstPtr(new VoxelPluginConfig::ParamDescription<double>("max_obstacle_height", "double", 0, "Max Obstacle Height", "", &VoxelPluginConfig::max_obstacle_height)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(VoxelPluginConfig::AbstractParamDescriptionConstPtr(new VoxelPluginConfig::ParamDescription<double>("max_obstacle_height", "double", 0, "Max Obstacle Height", "", &VoxelPluginConfig::max_obstacle_height)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.origin_z = 0.0;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.origin_z = std::numeric_limits<double>::infinity();
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.origin_z = 0.0;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(VoxelPluginConfig::AbstractParamDescriptionConstPtr(new VoxelPluginConfig::ParamDescription<double>("origin_z", "double", 0, "The z origin of the map in meters.", "", &VoxelPluginConfig::origin_z)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(VoxelPluginConfig::AbstractParamDescriptionConstPtr(new VoxelPluginConfig::ParamDescription<double>("origin_z", "double", 0, "The z origin of the map in meters.", "", &VoxelPluginConfig::origin_z)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.z_resolution = 0.0;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.z_resolution = 50.0;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.z_resolution = 0.2;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(VoxelPluginConfig::AbstractParamDescriptionConstPtr(new VoxelPluginConfig::ParamDescription<double>("z_resolution", "double", 0, "The z resolution of the map in meters/cell.", "", &VoxelPluginConfig::z_resolution)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(VoxelPluginConfig::AbstractParamDescriptionConstPtr(new VoxelPluginConfig::ParamDescription<double>("z_resolution", "double", 0, "The z resolution of the map in meters/cell.", "", &VoxelPluginConfig::z_resolution)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.z_voxels = 0;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.z_voxels = 16;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.z_voxels = 10;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(VoxelPluginConfig::AbstractParamDescriptionConstPtr(new VoxelPluginConfig::ParamDescription<int>("z_voxels", "int", 0, "The number of voxels to in each vertical column.", "", &VoxelPluginConfig::z_voxels)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(VoxelPluginConfig::AbstractParamDescriptionConstPtr(new VoxelPluginConfig::ParamDescription<int>("z_voxels", "int", 0, "The number of voxels to in each vertical column.", "", &VoxelPluginConfig::z_voxels)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.unknown_threshold = 0;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.unknown_threshold = 16;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.unknown_threshold = 15;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(VoxelPluginConfig::AbstractParamDescriptionConstPtr(new VoxelPluginConfig::ParamDescription<int>("unknown_threshold", "int", 0, "The number of unknown cells allowed in a column considered to be known", "", &VoxelPluginConfig::unknown_threshold)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(VoxelPluginConfig::AbstractParamDescriptionConstPtr(new VoxelPluginConfig::ParamDescription<int>("unknown_threshold", "int", 0, "The number of unknown cells allowed in a column considered to be known", "", &VoxelPluginConfig::unknown_threshold)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.mark_threshold = 0;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.mark_threshold = 16;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.mark_threshold = 0;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(VoxelPluginConfig::AbstractParamDescriptionConstPtr(new VoxelPluginConfig::ParamDescription<int>("mark_threshold", "int", 0, "The maximum number of marked cells allowed in a column considered to be free", "", &VoxelPluginConfig::mark_threshold)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(VoxelPluginConfig::AbstractParamDescriptionConstPtr(new VoxelPluginConfig::ParamDescription<int>("mark_threshold", "int", 0, "The maximum number of marked cells allowed in a column considered to be free", "", &VoxelPluginConfig::mark_threshold)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __min__.combination_method = 0;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __max__.combination_method = 2;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __default__.combination_method = 1;
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.abstract_parameters.push_back(VoxelPluginConfig::AbstractParamDescriptionConstPtr(new VoxelPluginConfig::ParamDescription<int>("combination_method", "int", 0, "Method for combining two layers", "{'enum': [{'name': 'Overwrite', 'type': 'int', 'value': 0, 'srcline': 16, 'srcfile': '/home/maxwell/Desktop/IC_protobot/catkin_ws/src/navigation/costmap_2d/cfg/VoxelPlugin.cfg', 'description': 'Overwrite values', 'ctype': 'int', 'cconsttype': 'const int'}, {'name': 'Maximum', 'type': 'int', 'value': 1, 'srcline': 17, 'srcfile': '/home/maxwell/Desktop/IC_protobot/catkin_ws/src/navigation/costmap_2d/cfg/VoxelPlugin.cfg', 'description': 'Take the maximum of the values', 'ctype': 'int', 'cconsttype': 'const int'}, {'name': 'Nothing', 'type': 'int', 'value': 99, 'srcline': 18, 'srcfile': '/home/maxwell/Desktop/IC_protobot/catkin_ws/src/navigation/costmap_2d/cfg/VoxelPlugin.cfg', 'description': 'Do nothing', 'ctype': 'int', 'cconsttype': 'const int'}], 'enum_description': 'Method for combining layers enum'}", &VoxelPluginConfig::combination_method)));
//#line 291 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __param_descriptions__.push_back(VoxelPluginConfig::AbstractParamDescriptionConstPtr(new VoxelPluginConfig::ParamDescription<int>("combination_method", "int", 0, "Method for combining two layers", "{'enum': [{'name': 'Overwrite', 'type': 'int', 'value': 0, 'srcline': 16, 'srcfile': '/home/maxwell/Desktop/IC_protobot/catkin_ws/src/navigation/costmap_2d/cfg/VoxelPlugin.cfg', 'description': 'Overwrite values', 'ctype': 'int', 'cconsttype': 'const int'}, {'name': 'Maximum', 'type': 'int', 'value': 1, 'srcline': 17, 'srcfile': '/home/maxwell/Desktop/IC_protobot/catkin_ws/src/navigation/costmap_2d/cfg/VoxelPlugin.cfg', 'description': 'Take the maximum of the values', 'ctype': 'int', 'cconsttype': 'const int'}, {'name': 'Nothing', 'type': 'int', 'value': 99, 'srcline': 18, 'srcfile': '/home/maxwell/Desktop/IC_protobot/catkin_ws/src/navigation/costmap_2d/cfg/VoxelPlugin.cfg', 'description': 'Do nothing', 'ctype': 'int', 'cconsttype': 'const int'}], 'enum_description': 'Method for combining layers enum'}", &VoxelPluginConfig::combination_method)));
//#line 246 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      Default.convertParams();
//#line 246 "/opt/ros/noetic/lib/python3/dist-packages/dynamic_reconfigure/parameter_generator_catkin.py"
      __group_descriptions__.push_back(VoxelPluginConfig::AbstractGroupDescriptionConstPtr(new VoxelPluginConfig::GroupDescription<VoxelPluginConfig::DEFAULT, VoxelPluginConfig>(Default)));
//#line 369 "/opt/ros/noetic/share/dynamic_reconfigure/cmake/../templates/ConfigType.h.template"

      for (std::vector<VoxelPluginConfig::AbstractGroupDescriptionConstPtr>::const_iterator i = __group_descriptions__.begin(); i != __group_descriptions__.end(); ++i)
      {
        __description_message__.groups.push_back(**i);
      }
      __max__.__toMessage__(__description_message__.max, __param_descriptions__, __group_descriptions__);
      __min__.__toMessage__(__description_message__.min, __param_descriptions__, __group_descriptions__);
      __default__.__toMessage__(__description_message__.dflt, __param_descriptions__, __group_descriptions__);
    }
    std::vector<VoxelPluginConfig::AbstractParamDescriptionConstPtr> __param_descriptions__;
    std::vector<VoxelPluginConfig::AbstractGroupDescriptionConstPtr> __group_descriptions__;
    VoxelPluginConfig __max__;
    VoxelPluginConfig __min__;
    VoxelPluginConfig __default__;
    dynamic_reconfigure::ConfigDescription __description_message__;

    static const VoxelPluginConfigStatics *get_instance()
    {
      // Split this off in a separate function because I know that
      // instance will get initialized the first time get_instance is
      // called, and I am guaranteeing that get_instance gets called at
      // most once.
      static VoxelPluginConfigStatics instance;
      return &instance;
    }
  };

  inline const dynamic_reconfigure::ConfigDescription &VoxelPluginConfig::__getDescriptionMessage__()
  {
    return __get_statics__()->__description_message__;
  }

  inline const VoxelPluginConfig &VoxelPluginConfig::__getDefault__()
  {
    return __get_statics__()->__default__;
  }

  inline const VoxelPluginConfig &VoxelPluginConfig::__getMax__()
  {
    return __get_statics__()->__max__;
  }

  inline const VoxelPluginConfig &VoxelPluginConfig::__getMin__()
  {
    return __get_statics__()->__min__;
  }

  inline const std::vector<VoxelPluginConfig::AbstractParamDescriptionConstPtr> &VoxelPluginConfig::__getParamDescriptions__()
  {
    return __get_statics__()->__param_descriptions__;
  }

  inline const std::vector<VoxelPluginConfig::AbstractGroupDescriptionConstPtr> &VoxelPluginConfig::__getGroupDescriptions__()
  {
    return __get_statics__()->__group_descriptions__;
  }

  inline const VoxelPluginConfigStatics *VoxelPluginConfig::__get_statics__()
  {
    const static VoxelPluginConfigStatics *statics;

    if (statics) // Common case
      return statics;

    boost::mutex::scoped_lock lock(dynamic_reconfigure::__init_mutex__);

    if (statics) // In case we lost a race.
      return statics;

    statics = VoxelPluginConfigStatics::get_instance();

    return statics;
  }

//#line 16 "/home/maxwell/Desktop/IC_protobot/catkin_ws/src/navigation/costmap_2d/cfg/VoxelPlugin.cfg"
      const int VoxelPlugin_Overwrite = 0;
//#line 17 "/home/maxwell/Desktop/IC_protobot/catkin_ws/src/navigation/costmap_2d/cfg/VoxelPlugin.cfg"
      const int VoxelPlugin_Maximum = 1;
//#line 18 "/home/maxwell/Desktop/IC_protobot/catkin_ws/src/navigation/costmap_2d/cfg/VoxelPlugin.cfg"
      const int VoxelPlugin_Nothing = 99;
}

#undef DYNAMIC_RECONFIGURE_FINAL

#endif // __VOXELPLUGINRECONFIGURATOR_H__
