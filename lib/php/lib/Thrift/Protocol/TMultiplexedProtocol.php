<?php

/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements. See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership. The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 * @package thrift.protocol
 */

namespace Thrift\Protocol;

use Thrift\Protocol\TProtocolDecorator;
use Thrift\Type\TMessageType;

class TMultiplexedProtocol extends TProtocolDecorator {

  const SEPARATOR = ':';

  private $SERVICE_NAME;

  public function __construct($protocol, $serviceName) {
    parent::__construct($protocol);
    $this->SERVICE_NAME = $serviceName;
  }

  public function writeMessageBegin($name, $type, $seqid) {
    if ($type == TMessageType::CALL || $type == TMessageType::ONEWAY) {
      parent::writeMessageBegin($this->SERVICE_NAME . self::SEPARATOR . $name, $type, $seqid);
    } else {
      parent::writeMessageBegin($name, $type, $seqid);
    }
  }
}
