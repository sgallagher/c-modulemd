/*
 * This file is part of libmodulemd
 * Copyright (C) 2018 Red Hat, Inc.
 *
 * Fedora-License-Identifier: MIT
 * SPDX-2.0-License-Identifier: MIT
 * SPDX-3.0-License-Identifier: MIT
 *
 * This program is free software.
 * For more information on the license, see COPYING.
 * For more information on free software, see <https://www.gnu.org/philosophy/free-sw.en.html>.
 */

#pragma once

#include <glib-object.h>
#include "modulemd-buildopts.h"
#include "modulemd-component.h"
#include "modulemd-component-module.h"
#include "modulemd-component-rpm.h"
#include "modulemd-dependencies.h"
#include "modulemd-module-stream.h"
#include "modulemd-profile.h"
#include "modulemd-service-level.h"

G_BEGIN_DECLS

/**
 * SECTION: modulemd-module-stream-v2
 * @title: Modulemd.ModuleStreamV2
 * @stability: stable
 * @short_description: The data to represent a stream of a module as described
 * by a modulemd YAML document of version 2.
 */

#define MODULEMD_TYPE_MODULE_STREAM_V2 (modulemd_module_stream_v2_get_type ())

G_DECLARE_FINAL_TYPE (ModulemdModuleStreamV2,
                      modulemd_module_stream_v2,
                      MODULEMD,
                      MODULE_STREAM_V2,
                      ModulemdModuleStream)


/**
 * modulemd_module_stream_v2_new:
 * @module_name: (in) (nullable): The name of this module.
 * @module_stream: (in) (nullable): The name of this module stream.
 *
 * Returns: (transfer full): A newly-allocated #ModulemdModuleStreamV2 object,
 * with the specified module and stream names, if provided.
 *
 * Since: 2.0
 */
ModulemdModuleStreamV2 *
modulemd_module_stream_v2_new (const gchar *module_name,
                               const gchar *module_stream);


/* ===== Properties ====== */


/**
 * modulemd_module_stream_v2_set_arch:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @arch: (in): The module artifact architecture.
 *
 * Set the module artifact architecture.
 *
 * Since: 2.0
 */
void
modulemd_module_stream_v2_set_arch (ModulemdModuleStreamV2 *self,
                                    const gchar *arch);


/**
 * modulemd_module_stream_v2_get_arch:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 *
 * Returns: (transfer none): The module artifact architecture.
 *
 * Since: 2.0
 */
const gchar *
modulemd_module_stream_v2_get_arch (ModulemdModuleStreamV2 *self);


/**
 * modulemd_module_stream_v2_set_buildopts:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @buildopts: (in) (transfer none): A #ModulemdBuildOpts object describing
 * build options that apply globally to components in this module.
 *
 * Set build options for this module's components.
 *
 * Since: 2.0
 */
void
modulemd_module_stream_v2_set_buildopts (ModulemdModuleStreamV2 *self,
                                         ModulemdBuildopts *buildopts);


/**
 * modulemd_module_stream_v2_get_buildopts:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 *
 * Returns: (transfer none): The build options for this module's components.
 *
 * Since: 2.0
 */
ModulemdBuildopts *
modulemd_module_stream_v2_get_buildopts (ModulemdModuleStreamV2 *self);


/**
 * modulemd_module_stream_v2_set_community:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @community: (in): The upstream community website for this module.
 *
 * Set the module community website address.
 *
 * Since: 2.0
 */
void
modulemd_module_stream_v2_set_community (ModulemdModuleStreamV2 *self,
                                         const gchar *community);


/**
 * modulemd_module_stream_v2_get_community:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 *
 * Returns: (transfer none): The module community website address.
 *
 * Since: 2.0
 */
const gchar *
modulemd_module_stream_v2_get_community (ModulemdModuleStreamV2 *self);


/**
 * modulemd_module_stream_v2_set_description:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @description: (in): The untranslated description of this module.
 *
 * Set the module description.
 *
 * Since: 2.0
 */
void
modulemd_module_stream_v2_set_description (ModulemdModuleStreamV2 *self,
                                           const gchar *description);


/**
 * modulemd_module_stream_v2_get_description:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 *
 * Returns: (transfer none): The module description.
 *
 * Since: 2.0
 */
const gchar *
modulemd_module_stream_v2_get_description (ModulemdModuleStreamV2 *self);


/**
 * modulemd_module_stream_v2_set_documentation:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @documentation: (in): The upstream documentation website for this module.
 *
 * Set the module documentation website address.
 *
 * Since: 2.0
 */
void
modulemd_module_stream_v2_set_documentation (ModulemdModuleStreamV2 *self,
                                             const gchar *documentation);


/**
 * modulemd_module_stream_v2_get_documentation:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 *
 * Returns: (transfer none): The module documentation website address.
 *
 * Since: 2.0
 */
const gchar *
modulemd_module_stream_v2_get_documentation (ModulemdModuleStreamV2 *self);


/**
 * modulemd_module_stream_v2_set_summary:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @summary: (in): The untranslated summary of this module.
 *
 * Set the module summary.
 *
 * Since: 2.0
 */
void
modulemd_module_stream_v2_set_summary (ModulemdModuleStreamV2 *self,
                                       const gchar *summary);


/**
 * modulemd_module_stream_v2_get_summary:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 *
 * Returns: (transfer none): The module summary.
 *
 * Since: 2.0
 */
const gchar *
modulemd_module_stream_v2_get_summary (ModulemdModuleStreamV2 *self);


/**
 * modulemd_module_stream_v2_set_tracker:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @tracker: (in): The upstream bug tracker website for this module.
 *
 * Set the module bug tracker website address.
 *
 * Since: 2.0
 */
void
modulemd_module_stream_v2_set_tracker (ModulemdModuleStreamV2 *self,
                                       const gchar *tracker);


/**
 * modulemd_module_stream_v2_get_tracker:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 *
 * Returns: (transfer none): The module bug tracker website address.
 *
 * Since: 2.0
 */
const gchar *
modulemd_module_stream_v2_get_tracker (ModulemdModuleStreamV2 *self);


/* ===== Non-property Methods ===== */


/**
 * modulemd_module_stream_v2_add_component:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @component: (in) (transfer none): A #ModulemdComponent to be added to this
 * module stream.
 *
 * Add a component definition to the module.
 *
 * Since: 2.0
 */
void
modulemd_module_stream_v2_add_component (ModulemdModuleStreamV2 *self,
                                         ModulemdComponent *component);


/**
 * modulemd_module_stream_v2_remove_module_component:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @component_name: (in): The name of the component to remove from the module
 * stream.
 *
 * Remove a component from this module stream.
 *
 * Since: 2.0
 */
void
modulemd_module_stream_v2_remove_module_component (
  ModulemdModuleStreamV2 *self, const gchar *component_name);


/**
 * modulemd_module_stream_v2_remove_rpm_component:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @component_name: (in): The name of the component to remove from the module
 * stream.
 *
 * Remove a component from this module stream.
 *
 * Since: 2.0
 */
void
modulemd_module_stream_v2_remove_rpm_component (ModulemdModuleStreamV2 *self,
                                                const gchar *component_name);


/**
 * modulemd_module_stream_v2_get_module_component_names_as_strv: (rename-to modulemd_module_stream_v2_get_module_component_names)
 * @self: (in): This #ModulemdModuleStreamV2 object.
 *
 * Returns: (transfer full): An ordered list of module component names included
 * in this stream.
 *
 * Since: 2.0
 */
GStrv
modulemd_module_stream_v2_get_module_component_names_as_strv (
  ModulemdModuleStreamV2 *self);

/**
 * modulemd_module_stream_v2_get_rpm_component_names_as_strv: (rename-to modulemd_module_stream_v2_get_rpm_component_names)
 * @self: (in): This #ModulemdModuleStreamV2 object.
 *
 * Returns: (transfer full): An ordered list of RPM component names included
 * in this stream.
 *
 * Since: 2.0
 */
GStrv
modulemd_module_stream_v2_get_rpm_component_names_as_strv (
  ModulemdModuleStreamV2 *self);


/**
 * modulemd_module_stream_v2_get_module_component:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @component_name: (in): The name of the component to retrieve.
 *
 * Returns: (transfer none): The module component matching @component name if
 * it exists, else NULL.
 *
 * Since: 2.0
 */
ModulemdComponentModule *
modulemd_module_stream_v2_get_module_component (ModulemdModuleStreamV2 *self,
                                                const gchar *component_name);


/**
 * modulemd_module_stream_v2_get_rpm_component:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @component_name: (in): The name of the component to retrieve.
 *
 * Returns: (transfer none): The RPM component matching @component name if it
 * exists, else NULL.
 *
 * Since: 2.0
 */
ModulemdComponentRpm *
modulemd_module_stream_v2_get_rpm_component (ModulemdModuleStreamV2 *self,
                                             const gchar *component_name);


/**
 * modulemd_module_stream_v2_add_content_license:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @license: (in): A license under which one or more of the components of this
 * module stream are distributed.
 *
 * Since: 2.0
 */
void
modulemd_module_stream_v2_add_content_license (ModulemdModuleStreamV2 *self,
                                               const gchar *license);


/**
 * modulemd_module_stream_v2_add_module_license:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @license: (in): A license under which this module stream is distributed.
 *
 * Since: 2.0
 */
void
modulemd_module_stream_v2_add_module_license (ModulemdModuleStreamV2 *self,
                                              const gchar *license);


/**
 * modulemd_module_stream_v2_remove_content_license:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @license: (in): A license to remove from the list. Has no effect if the
 * license is not present.
 *
 * Since: 2.0
 */
void
modulemd_module_stream_v2_remove_content_license (ModulemdModuleStreamV2 *self,
                                                  const gchar *license);


/**
 * modulemd_module_stream_v2_remove_module_license:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @license: (in): A license to remove from the list. Has no effect if the
 * license is not present.
 *
 * Since: 2.0
 */
void
modulemd_module_stream_v2_remove_module_license (ModulemdModuleStreamV2 *self,
                                                 const gchar *license);


/**
 * modulemd_module_stream_v2_get_content_licenses_as_strv: (rename-to modulemd_module_stream_v2_get_content_licenses)
 * @self: (in): This #ModulemdModuleStreamV2 object.
 *
 * Returns: (transfer full): An ordered list of licenses under which one or
 * more components of this module stream are released.
 *
 * Since: 2.0
 */
GStrv
modulemd_module_stream_v2_get_content_licenses_as_strv (
  ModulemdModuleStreamV2 *self);


/**
 * modulemd_module_stream_v2_get_module_licenses_as_strv: (rename-to modulemd_module_stream_v2_get_module_licenses)
 * @self: (in): This #ModulemdModuleStreamV2 object.
 *
 * Returns: (transfer full): An ordered list of licenses under which this
 * module stream is released.
 *
 * Since: 2.0
 */
GStrv
modulemd_module_stream_v2_get_module_licenses_as_strv (
  ModulemdModuleStreamV2 *self);


/**
 * modulemd_module_stream_v2_add_profile:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @profile: (in) (transfer none): A #ModulemdProfile for this module stream.
 *
 * Adds a profile definition to this module stream.
 *
 * Since: 2.0
 */
void
modulemd_module_stream_v2_add_profile (ModulemdModuleStreamV2 *self,
                                       ModulemdProfile *profile);


/**
 * modulemd_module_stream_v2_clear_profiles:
 * @self: (in): This #ModulemdModuleStreamV1 object.
 *
 * Removes all profiles from this module stream.
 *
 * Since: 2.0
 */
void
modulemd_module_stream_v2_clear_profiles (ModulemdModuleStreamV2 *self);


/**
 * modulemd_module_stream_v2_get_profile_names_as_strv: (rename-to modulemd_module_stream_v2_get_profile_names)
 * @self: (in): This #ModulemdModuleStreamV2 object.
 *
 * Returns: (transfer full): An ordered list of profile names associated with
 * this module stream.
 *
 * Since: 2.0
 */
GStrv
modulemd_module_stream_v2_get_profile_names_as_strv (
  ModulemdModuleStreamV2 *self);


/**
 * modulemd_module_stream_v2_get_profile:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @profile_name: (in): The name of a profile to retrieve.
 *
 * Returns: (transfer none): The requested profile definition if present in the
 * module stream. NULL otherwise.
 *
 * Since: 2.0
 */
ModulemdProfile *
modulemd_module_stream_v2_get_profile (ModulemdModuleStreamV2 *self,
                                       const gchar *profile_name);


/**
 * modulemd_module_stream_v2_add_rpm_api:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @rpm: (in): The name of a binary RPM present in this module that is
 * considered stable public API.
 *
 * Since: 2.0
 */
void
modulemd_module_stream_v2_add_rpm_api (ModulemdModuleStreamV2 *self,
                                       const gchar *rpm);


/**
 * modulemd_module_stream_v2_remove_rpm_api:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @rpm: (in): A binary RPM name to remove from the list of stable public API.
 *
 * Since: 2.0
 */
void
modulemd_module_stream_v2_remove_rpm_api (ModulemdModuleStreamV2 *self,
                                          const gchar *rpm);


/**
 * modulemd_module_stream_v2_get_rpm_api_as_strv: (rename-to modulemd_module_stream_v2_get_rpm_api)
 * @self: (in): This #ModulemdModuleStreamV2 object.
 *
 * Returns: (transfer full): An ordered list of binary RPM names that forms
 * the public API of this module stream.
 *
 * Since: 2.0
 */
GStrv
modulemd_module_stream_v2_get_rpm_api_as_strv (ModulemdModuleStreamV2 *self);


/**
 * modulemd_module_stream_v2_add_rpm_artifact:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @nevr: (in): The NEVR of a binary RPM present in this module stream.
 *
 * Since: 2.0
 */
void
modulemd_module_stream_v2_add_rpm_artifact (ModulemdModuleStreamV2 *self,
                                            const gchar *nevr);


/**
 * modulemd_module_stream_v2_remove_rpm_artifact:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @nevr: (in): An RPM NEVR to remove from the list of artifacts.
 *
 * Since: 2.0
 */
void
modulemd_module_stream_v2_remove_rpm_artifact (ModulemdModuleStreamV2 *self,
                                               const gchar *nevr);


/**
 * modulemd_module_stream_v2_get_rpm_artifacts_as_strv: (rename-to modulemd_module_stream_v2_get_rpm_artifacts)
 * @self: (in): This #ModulemdModuleStreamV2 object.
 *
 * Returns: (transfer full): An ordered list of RPM NEVRs are included in this
 * module stream.
 *
 * Since: 2.0
 */
GStrv
modulemd_module_stream_v2_get_rpm_artifacts_as_strv (
  ModulemdModuleStreamV2 *self);


/**
 * modulemd_module_stream_v2_add_rpm_filter:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @rpm: (in): The name of a binary RPM to filter out of this module stream.
 *
 * Since: 2.0
 */
void
modulemd_module_stream_v2_add_rpm_filter (ModulemdModuleStreamV2 *self,
                                          const gchar *rpm);


/**
 * modulemd_module_stream_v2_remove_rpm_filter:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @rpm: (in): A binary RPM name to remove from the filter list.
 *
 * Since: 2.0
 */
void
modulemd_module_stream_v2_remove_rpm_filter (ModulemdModuleStreamV2 *self,
                                             const gchar *rpm);


/**
 * modulemd_module_stream_v2_get_rpm_filters_as_strv: (rename-to modulemd_module_stream_v2_get_rpm_filters)
 * @self: (in): This #ModulemdModuleStreamV2 object.
 *
 * Returns: (transfer full): An ordered list of binary RPM names that are
 * filtered out of this module stream.
 *
 * Since: 2.0
 */
GStrv
modulemd_module_stream_v2_get_rpm_filters_as_strv (
  ModulemdModuleStreamV2 *self);


/**
 * modulemd_module_stream_v2_add_servicelevel:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @servicelevel: (in) (transfer none): A #ModulemdServiceLevel for this module stream.
 *
 * Adds a servicelevel definition to this module stream.
 *
 * Since: 2.0
 */
void
modulemd_module_stream_v2_add_servicelevel (
  ModulemdModuleStreamV2 *self, ModulemdServiceLevel *servicelevel);


/**
 * modulemd_module_stream_v2_clear_servicelevels:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 *
 * Removes all servicelevels from this module stream.
 *
 * Since: 2.0
 */
void
modulemd_module_stream_v2_clear_servicelevels (ModulemdModuleStreamV2 *self);


/**
 * modulemd_module_stream_v2_get_servicelevel_names_as_strv: (rename-to modulemd_module_stream_v2_get_servicelevel_names)
 * @self: (in): This #ModulemdModuleStreamV2 object.
 *
 * Returns: (transfer full): An ordered list of servicelevel names associated with
 * this module stream.
 *
 * Since: 2.0
 */
GStrv
modulemd_module_stream_v2_get_servicelevel_names_as_strv (
  ModulemdModuleStreamV2 *self);


/**
 * modulemd_module_stream_v2_get_servicelevel:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @servicelevel_name: (in): The name of a servicelevel to retrieve.
 *
 * Returns: (transfer none): The requested servicelevel definition if present in the
 * module stream. NULL otherwise.
 *
 * Since: 2.0
 */
ModulemdServiceLevel *
modulemd_module_stream_v2_get_servicelevel (ModulemdModuleStreamV2 *self,
                                            const gchar *servicelevel_name);


/**
 * modulemd_module_stream_v2_add_dependencies:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @deps: (in): A #ModulemdDependencies object to add to the list for this
 * module stream.
 *
 * Add a #ModulemdDependencies object to the list of dependencies for this
 * module stream.
 *
 * Since: 2.0
 */
void
modulemd_module_stream_v2_add_dependencies (ModulemdModuleStreamV2 *self,
                                            ModulemdDependencies *deps);


/**
 * modulemd_module_stream_v2_get_dependencies:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 *
 * Return the list of #ModulemdDependencies objects as a GPtrArray
 *
 * Returns: (transfer none) (element-type ModulemdDependencies): A list of
 * all #ModulemdDependencies objects associated with this module stream.
 */
GPtrArray *
modulemd_module_stream_v2_get_dependencies (ModulemdModuleStreamV2 *self);


/**
 * modulemd_module_stream_v2_set_xmd:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 * @xmd: (in) (transfer full): A #GVariant representing arbitrary YAML.
 *
 * Sets the eXtensible MetaData (XMD) for this module. XMD is arbitrary YAML
 * data that will be set and returned as-is (with the exception that the
 * ordering of mapping keys is not defined). Useful for carrying private data.
 *
 * This function assumes ownership of the XMD #GVariant and thus should not be
 * freed by the caller.
 *
 * Since: 2.0
 */
void
modulemd_module_stream_v2_set_xmd (ModulemdModuleStreamV2 *self,
                                   GVariant *xmd);


/**
 * modulemd_module_stream_v2_get_xmd:
 * @self: (in): This #ModulemdModuleStreamV2 object.
 *
 * Returns: (transfer none): The extensible metadata block as a GVariant.
 */
GVariant *
modulemd_module_stream_v2_get_xmd (ModulemdModuleStreamV2 *self);


G_END_DECLS
