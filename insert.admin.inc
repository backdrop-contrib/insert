<?php
/**
 * @file
 * Admin page callbacks for the Insert module.
 */

/**
 * Page callback: Lists insert-enabled fields for quick reference.
 *
 * @see insert_menu()
 */
function insert_fields_list() {
  $instances = field_info_instances();
  $field_types = field_info_field_types();
  $bundles = field_info_bundles();

  $header = array(
    array('data' => t('Field name'), 'field' => 'field_name', 'sort' => 'asc'),
    array('data' => t('Field type'), 'field' => 'field_type', 'class' => array(RESPONSIVE_PRIORITY_MEDIUM)),
    array('data' => t('Content type'), 'field' => 'bundle', 'class' => array(RESPONSIVE_PRIORITY_LOW)),
    t('Insert presets'),
  );
  $rows = array();
  $insert_widgets = insert_widgets();
  $insert_styles = insert_styles_list();
  $n = 0;

  foreach ($instances as $entity_type => $type_bundles) {
    foreach ($type_bundles as $bundle => $bundle_instances) {
      foreach ($bundle_instances as $field_name => $instance) {

        // only include widgets with insert_styles activated
        if (empty($instance['widget']['settings']['insert_styles'])) {
          continue;
        }

        $field = field_info_field($field_name);
        $rows[$n]['class'] = $field['locked'] ? array('menu-disabled') : array('');

        // Add the current instance.
        $admin_path = _field_ui_bundle_admin_path($entity_type, $bundle);

        $field_label = $instances[$entity_type][$bundle][$field_name]['label'];
        $bundle_label = $bundles[$entity_type][$bundle]['label'];

        $rows[$n]['data']['field_name'] = $field['locked'] ? t('@field_name (Locked)', array('@field_name' => $field_name)) : $field_name;
        $rows[$n]['data']['field_type'] = $field_types[$field['type']]['label'];
        $rows[$n]['data']['bundle'] = $bundle_label;


        if ($admin_path) {
          $bundle_manage_fields_link = $admin_path . '/fields';
          $field_configure_link = $bundle_manage_fields_link . '/' . $field_name;

          $rows[$n]['data']['bundle'] = t('<a href="@bundle_manage_fields_link">@bundle_label</a>', array('@bundle_manage_fields_link' => url($bundle_manage_fields_link), '@bundle_label' => $bundle_label));

          $rows[$n]['data']['field_name'] = t('<a href="@field_configure_link">@field_label</a>', array('@field_configure_link' => url($field_configure_link), '@field_label' => $field_name));
        }

        if (empty($instance['widget']['settings']['insert'])) {
          $rows[$n]['data']['styles'] = array('Not enabled');
        }
        else {
          $rows[$n]['data']['styles'] = array_intersect_key($insert_styles, array_filter($instance['widget']['settings']['insert_styles']));
        }

        $n++;
      }
    }
  }
  foreach ($rows as $n => $cell) {
    // render the items of the "styles" column as a list.
    $rows[$n]['data']['styles'] = theme('item_list', array('items' => $rows[$n]['data']['styles']));
  }

  // Sort columns.
  $sort = tablesort_get_sort($header);
  $order = tablesort_get_order($header);
  switch($order['sql']) {
    case 'field_name':
      uasort($rows, function($a, $b) {
        return strcasecmp($a['data']['field_name'], $b['data']['field_name']);
      });
      break;
    case 'field_type':
      uasort($rows, function($a, $b) {
        return strcasecmp($a['data']['field_type'], $b['data']['field_type']);
      });
      break;
    case 'bundle':
      uasort($rows, function($a, $b) {
        return strcasecmp($a['data']['bundle'], $b['data']['bundle']);
      });
      break;
  }
  if ($sort == 'desc') {
    $rows = array_reverse($rows);
  }

  $output = theme('table', array('header' => $header, 'rows' => $rows, 'empty' => t('No fields have been defined yet.'),));

  return $output;
}
